clc;
clear;
F1=load("C:\Users\Peter Wang\Downloads\CPFH2_HWang\cmake-build-debug\changeofRadius");
F2=load("C:\Users\Peter Wang\Downloads\CPFH2_HWang\cmake-build-debug\changeofRadius2");
F3=load("C:\Users\Peter Wang\Downloads\CPFH2_HWang\cmake-build-debug\changeofRadius3");
F4=load("C:\Users\Peter Wang\Downloads\CPFH2_HWang\cmake-build-debug\changeofRadius4");
s1=size(F1);
s2=size(F2);
s3=size(F3);
s4=size(F4);
F1(s1(1),:)=[];
F2(s2(1),:)=[];
F3(s3(1),:)=[];
F4(s4(1),:)=[];
plot(F1(:,2),F1(:,1),F2(:,2),F2(:,1),F3(:,2),F3(:,1),F4(:,2),F4(:,1));
title('Time vs. Change of Radius');
xlabel('Radius');
ylabel('Time');
legend('Tin/Lead (60/40)','Tin/Lead (56/44)','Tin/Lead (50/50)','Tin/Lead (43/57)');