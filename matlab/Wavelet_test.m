%Author: Qin Shuo
%Date: 2015.9.21
%Organization: RC-MIC(CUHK)
%Description:
%  This is a test file for ECG signal process in MRI environment
%  Basic Method is slide window
%  Method is Mallat's Pyramid Algorithm

%load data from file
%[filename,filepath] = uigetfile('*.*');
fullname=fullfile(filepath,filename);
fullname='C:/D/wavelet1d_C/build/algorithm/test.txt'

%decompose level
level=5;

%data resources
Src=load(fullname);
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


%%%   plot here  %%%

figure(1)
row=3;
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




