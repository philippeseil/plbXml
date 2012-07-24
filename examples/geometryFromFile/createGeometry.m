#!/usr/bin/octave

clear

nx = 301;
ny = 101;

fs = 0.1;

domain = zeros(nx,ny);

% domain walls
domain(:,[1,ny]) = 1;

ind = zeros(nx,ny);
% create random porous media in middle of domain
ind(51:251,:) = rand(201,ny) < fs;
domain = ind | domain;

f = fopen("domain.txt","w+");
for i=1:ny
  fprintf(f,"%d ",domain(:,i)');
  fprintf(f,"\n");
end
fclose(f);

