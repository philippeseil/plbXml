nx = 701;
ny = 101;

domain = zeros(nx,ny);

domain(:,1) = 1;
domain(1:101,ny) = 1;
domain(152:nx,ny) = 1;

domain(300:330,40:58) = 1;
domain(301:329,41:57) = 2;

f = fopen("domain.txt","w+");
for i=1:nx
  fprintf(f,"%d ",domain(i,:));
  fprintf(f,"\n");
end
fclose(f);

