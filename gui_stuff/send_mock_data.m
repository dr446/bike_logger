 M = csvread('mock_SD_data.csv');
 arduinoCom = serial('COM5','BaudRate',9600);
 fopen(arduinoCom);
 
 for i = 1:size(M,1)
 fprintf(arduinoCom,'%i',M(i,:), async);
 fscanf(arduinoCom)    %this will read response
 end