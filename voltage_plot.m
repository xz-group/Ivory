figure
data1=importdata('SM4.data');
x1 = data1(1:1:157152,1);
y1 = data1(1:1:157152,2);




plot(x1,y1);

%axis([0 2000 0.3 1.5]); 
title('SM1')