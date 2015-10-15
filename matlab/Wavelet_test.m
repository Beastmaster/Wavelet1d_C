%Author: Qin Shuo
%Date: 2015.9.21
%Organization: RC-MIC(CUHK)
%Description:
%  This is a test file for ECG signal process in MRI environment
%  Basic Method is slide window
%  Method is Mallat's Pyramid Algorithm

%load data from file
%[filename,filepath] = uigetfile('*.*');
%fullname=fullfile(filepath,filename);
%if(filepath==0)
%    return
%end
%fullname='C:/D/wavelet1d_C/build/algorithm/test.txt'

%data resources
%Src=load(fullname);
Src = load('C:/Users/User/Desktop/wave/Wavelet1d_C/data/20150517101410.txt');
Src = Src(1:length(Src))
%%%%%   high pass filter   %%%%
% sample rate: 500Hz
% cut-off rate
% FIR parameters
% IIR parameters
% Numerator
%ACoef=[       0.9459771022203,    -14.1896565333,    99.32759573313,   -430.4195815102,  1291.258744531,   -2840.769237968,    4734.615396613,   -6087.362652788,      6087.362652788,   -4734.615396613,    2840.769237968,   -1291.258744531,      430.4195815102,   -99.32759573313,     14.1896565333,  -0.9459771022203 ];
% Denominator
%BCoef = [              1,   -14.88892701398,    103.4511442676,   -444.9722907869,     1325.047675801,   -2893.564561276,    4786.991147491,   -6109.272487078,      6064.201177665,   -4681.822400104,     2788.39109625,   -1258.114603752,      416.2841149536,    -95.3587000897,    13.52248634932,  -0.8948726779251  ];
%Des = filter(BCoef,ACoef,Src)
if(0) 
    x = 0:1:17
    y = 0:1:17
    x(:)=0
    y(:)=0

    Des = []

    %loop begin
    for i = 1:length(Src)

        sum = x(1)*ACoef(1); 
        %filter
        for n=2:length(ACoef)
           sum = sum + ACoef(n) * x(n) - BCoef(n) * y(n);
        end
        sum = sum/BCoef(1)

        %shift data
        for j = 1:length(x)-1
            x(j+1) = x(j);
            y(j+1) = y(j);
        end
        x(1) = Src(i);
        y(1) = sum;

        Des = [Des ; sum];
    end
end


%decompose level
level=5;

%Src=Src(1:150);
%Src=[Src;Src;Src;Src;Src];
%Reconstructed data
Des=[];
%decompose window
window_width = 40
step         = round(1)
shift        = round(window_width/2)
delay        = window_width-step;

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



%%%%   moving average filter   %%%%
% un-proper reslult
if(0)
    x = 1:1:20;
    x(:) = 0;   % zeros x
    for i=1:1:length(Des)
       for j=1:1:length(x)-1
          x(j+1)=x(j); 
       end
       x(1) = Des(i);
       Des_y=[Des_y;Des(i)-mean(x)] ;
    end
end

%%%% differentiate function -- derivative %%%%
Des_y=[];
Des_y2=[];
Des_y3=[];
for i=5:1:length(Des)
   Des_y  = [Des_y;(Des(i)-Des(i-4))/4] ;
end
%%%% Squaring funciton %%%%
for i=1:1:length(Des_y)
   Des_y2 = [Des_y2;(Des_y(i)*Des_y(i))] ;
end 
%%%%  Integrate function %%%%
for i=61:1:length(Des_y2)
   Des_y3 = [Des_y3;sum(Des_y2(i-60:i))];
end

%%%%  Search peak  %%%%
peak = 4/5 *max(Des_y3(1:300));
dec=[];
flag1=0;
flag2=0;
for i=1:1:length(Des_y3)-3
    if Des_y3(i)>=peak
        flag1=1;
    else
        flag1=0;
    end
    if Des_y3(i+3)>=peak
        flag2=1;
    else
        flag2=0
    end
    if (flag2==1)&(flag1==0)
        dec = [dec;1]; 
    else
        dec = [dec;0];
    end
end

%%%%%   Use matlab implemented filter for test %%%%%
%enable test filter or not
if(0)
    df = designfilt('highpassiir', 'StopbandFrequency', .05, 'PassbandFrequency', 0.5, 'StopbandAttenuation', 60, 'PassbandRipple', 1, 'SampleRate', 500);
    sos = df.Coefficients;
    Des_y = filter(df,Des);
    %[BCoef,ACoef] = sos2ft(sos);
end


%%%   plot here  %%%

figure(1)
row=7;
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
% plot derivative
subplot(row,col,4)
plot(Des_y)
title('Derivative plot')
% plot squaring function
subplot(row,col,5)
plot(Des_y2)
title('Square plot')
% plot squaring function
subplot(row,col,6)
plot(Des_y3)
title('Integrated plot')
% plot peak
subplot(row,col,7)
plot(dec)
title('peak')

