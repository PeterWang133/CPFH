clc;
clear;

F=load("C:\Users\Peter Wang\Downloads\CPFH3_HWang\cmake-build-debug\CPFH3_HWang.txt");
plot(F(:,2),F(:,1));
title('Time vs. Heat Transfer Coefficient');
xlabel('Heat Transfer Coefficient');
ylabel('Time');
legend('Tested Material from Part 1');