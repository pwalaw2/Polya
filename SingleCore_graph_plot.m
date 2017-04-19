x1=[1.5230];
y1=[7.8994];
x2=[1.6734];
y2=[5.4772];
x3=[1.6733];
y3=[5.4888];
x4=[1.6734];
y4=[5.4988];





plot(x1,y1,'o',x2,y2,'o',x3,y3,'o',x4,y4,'o');
title('EDP V/s Performance (Cross-group DSE)');
xlabel('IPC (Performance)');
ylabel('EDP');
legend('Not-tuned/default parameters','Tuning different parameters with 2 level','Tuning different parameters with bimodal','Tuning different parameters with Return address stack');
%legend('Instruction fetch queue size','Instruction decode B/W','Instruction issue B/W','Run pipeline with in-order issue','Issue instructions down wrong execution paths','Instruction commit B/W','Register update unit size','Load/store queue size');