% Min Radius Graph
clc;
clear;
F1=load("C:\Users\Peter Wang\Downloads\CPFH2_HWang\cmake-build-debug\transientResponse");
F2=load("C:\Users\Peter Wang\Downloads\CPFH2_HWang\cmake-build-debug\transientResponse2");
F3=load("C:\Users\Peter Wang\Downloads\CPFH2_HWang\cmake-build-debug\transientResponse3");
F4=load("C:\Users\Peter Wang\Downloads\CPFH2_HWang\cmake-build-debug\transientResponse4");
plot(F1(:,1),F1(:,2),F2(:,1),F2(:,2),F3(:,1),F3(:,2),F4(:,1),F4(:,2));
title('Time vs. Temperature (Min Radius)');
xlabel('Time');
ylabel('Temperature');
legend('Tin/Lead (60/40)','Tin/Lead (56/44)','Tin/Lead (50/50)','Tin/Lead (43/57)');