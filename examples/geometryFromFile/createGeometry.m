#!/usr/bin/octave

clear

nx = 301;
ny = 101;

% solid fraction of the domain
fs = 0.1;

domain = zeros(nx,ny);

% domain walls
domain(:,[1,ny]) = 1;

ind = zeros(nx,ny);
% create random porous media in middle of domain
xl = ceil(ny/2);
xh = ceil(nx - ny/2);
dx = xh - xl;

ind(xl:xh,:) = rand(dx+1,ny) < fs;
domain = ind | domain;

f = fopen("domain.txt","w+");
for i=1:ny
  fprintf(f,"%d ",domain(:,i)');
  fprintf(f,"\n");
end
fclose(f);

