% Author: Qin Shuo
% Date: 2015.9.21
% Organization: RC-MIC(CUHK)
%
% Description: 
%  This file implement the orignal wavelet algorithm (pyramid algorithm)
%
% Uitility:
%  



%load data from file
%[filename,filepath] = uigetfile('*.*');
%fullname=fullfile(filepath,filename);

%source array
Src=1:1:20;
Func=10:-1:1;
level=5;

%%%   algorithm begin    %%%

%wavelet types
wave_type_list={'db4';'db5';'haar';'coif1';'sym2'};
type_choice = 1;
wave_type = wave_type_list{type_choice};

%wavelet fileters
[Lo_D,Hi_D,Lo_R,Hi_R] = wfilters(wave_type);

%wavelet decompose
conv_len=length(Lo_D)
Res = conv(Src,Func);
Res = Res(length(Func):length(Src)-1);





%%%  plot here   %%%
row = 3;
col = 1;
figure(1)
% plot original signal
subplot(row,col,1)
plot(Src)
title('Original signal')
% plot filtered signal
subplot(row,col,2)
plot(Func)
title('Convolve function')
% plot one time filterd signal
subplot(row,col,3)
plot(Res)
title('Result')



