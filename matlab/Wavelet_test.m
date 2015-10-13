%Author: Qin Shuo
%Date: 2015.9.21
%Organization: RC-MIC(CUHK)
%Description:
%  This is a test file for ECG signal process in MRI environment
%  Basic Method is slide window
%  Method is Mallat's Pyramid Algorithm

%load data from file
[filename,filepath] = uigetfile('*.*');
fullname=fullfile(filepath,filename);
%fullname='C:/D/wavelet1d_C/build/algorithm/test.txt'

%decompose level
level=5;

%data resources
Src=load(fullname);

%enable test filter or not
if(0)
df = designfilt('highpassiir', 'StopbandFrequency', .45, 'PassbandFrequency', 1, 'StopbandAttenuation', 60, 'PassbandRipple', 1, 'SampleRate', 500);
Des = filter(df,Src)
plot(Des)
end

%Src=Src(1:150);
%Src=[Src;Src;Src;Src;Src];
%Reconstructed data
Des=[];
%decompose window
window_width = 256;
step         = round(window_width/200);
shift        = round(window_width/3);
overlap      = window_width-step;

%wavelet types
wave_type_list={'haar';'db4';'db5';'coif3';'coif4';'sym3';'sym4';};
type_choice = 2;
wave_type = wave_type_list{type_choice};


begin_=1;
step_ =step;
end_  =length(Src);
%end_= 0;

for i=begin_:step_:end_
%%%%   loop body   %%%%

%select some data from the source
if (i+window_width-1)>length(Src)
    continue
else
    data=Src(i:i+window_width-1);
end
%wavelet fileters
[Lo_D,Hi_D,Lo_R,Hi_R] = wfilters(wave_type);

%wavelet decompose 
[C,L]=wavedec(data,level,wave_type);

%wacelet reconstruct
re_data=wrcoef('a',C,L,wave_type,level);
%select points middle of the series
re_data=re_data(1+shift:step_+shift)

%%apply moving average to exclude pulse between steps
% proved useless
if i==1
else
ave_len=10;
%temp=Des(length(Des)-10:length(Des)); %select last 10 components in Des
    for j=1:ave_len
       %temp=[temp(j:length(temp));re_data(1:j)];
       %re_data(j)=mean(temp);
    end
end

%append to result(Des)
Des=[Des;re_data] ;
%%%    loop body  %%%%
end

%%%  one time wavelet %%%
[C2,L2]=wavedec(Src,level,wave_type);
Des2=wrcoef('a',C2,L2,wave_type,level);

%%% stationary wavelet algorithm %%%
%re_data=swt(Src,level,wave_type);
%Des3=swt(re_data,Lo_D,Hi_D);



%%%%%   high pass filter   %%%%
% sample rate: 500Hz
% cut-off rate
% FIR parameters
% IIR parameters

%ACoef = [0.97996108158527773000, -4.89980540792638840000,9.79961081585277680000,  -9.79961081585277680000,  4.89980540792638840000, -0.97996108158527773000]


ACoef=[  0.00000078581853600240,
        0.00000392909268001200,
        0.00000785818536002399,
        0.00000785818536002399,
        0.00000392909268001200,
        0.00000078581853600240]



%BCoef =[1.00000000000000000000,-4.95933444853386440000,9.83816341127570130000, -9.75847320197398460000,        4.83979404410087890000,        -0.96014980456165600000]
BCoef = [
            1.00000000000000000000,
        -4.59342139980768760000,
        8.45511522351013410000,
        -7.79491831804444860000,
        3.59890276805391320000,
        -0.66565253817136127000

]


x = 0:0.1:1
y = 0:0.1:1

Des_y = []

%loop begin
for i = 1:length(Des2)
	%shift data
	for j = 1:length(x)-1
		x(j+1) = x(j)
		y(j+1) = y(j)	
	end
	x(1) = Des2(i)
	y(1) = x(1)*ACoef(1)
	%filter
	for n=1:length(ACoef)
        y(1) = y(1) + ACoef(n) * x(n) - BCoef(n) * y(n);
	end
	
	Des_y = [Des_y;y(1)]
end



%%%   plot here  %%%

figure(1)
row=4;
col=1;
% plot original signal
subplot(row,col,1)
plot(Src(1:length(Des)))
title('Original signal')
% plot filtered signal
subplot(row,col,2)
plot(Des)
title('Filtered signal')
% plot one time filterd signal
subplot(row,col,3)
plot(Des2(1:length(Des)))
title('One time filter')
% plot high pass signal
subplot(row,col,4)
plot(Des_y(1:length(Des_y)))
title('One time filter')



