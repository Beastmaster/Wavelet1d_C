%Author: Qin Shuo
%Date: 2015.9.21
%Organization: RC-MIC(CUHK)
%Description:
%This is a test file for ECG signal process in MRI environment
%Basic Method is slide window
%

%load data from file
[filename,filepath] = uigetfile('*.*');
fullname=fullfile(filepath,filename);


%decompose level
level=5;

%data resources
Src=load(fullname);
%Reconstructed data
Des=[];
%decompose window
window_width = 100;
step          = 1;
overlap       = window_length-step;

%wavelet types
wave_type_list={'db4';'db5';'haar';'coif1';'sym2'};
type_choice = 1;
wave_type = wave_type_list{type_choice};


begin_=1;
step_=10;
end_=length(Src)-window_width;
%end_= 0;

for i=begin_:step_:end_
%%%%   loop body   %%%%

%select some data from the source
data=Src(i:i+window_width-1);

%wavelet fileters
[Lo_D,Hi_D,Lo_R,Hi_R] = wfilters(wave_type);

%wavelet decompose 
[C,L]=wavedec(data,level,wave_type);

%wacelet reconstruct
re_data=wrcoef('a',C,L,wave_type,level);

%select points and add to result(Des)
Des=[Des,re_data(1:1+step-1)] ;

%%%    loop body  %%%%
end


%%%   plot here  %%%

figure(1)
row=2;
col=1;
% plot original signal
subplot(row,col,1)
plot(Src)
title('Original signal')
% plot filtered signal
subplot(row,col,2)
plot(Des)
title('Filtered title')
