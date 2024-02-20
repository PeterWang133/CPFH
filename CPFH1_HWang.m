clear;  % Clears the command window
clc;    % Clears the workspace
close;  % Closes any figures

F=load('C:\Users\Peter Wang\Downloads\CPFL_HWang\cmake-build-debug\CPFH1_HWang');
plot(F(:,1),F(:,2));
title('Time vs. Temperature');
xlabel('Time');
ylabel('Temperature');
legend('Rate of Change');