/*
Copyright Mystic Mike (Mike Hosker)
mysticmike at gmail dot com
GPL 2++
*/
#include <stdio.h>
#include <math.h>

struct star {
double mag;
double ra;
double dec;
};

/* change this to render skybox at a different size */
#define BOX_SIZE 2048

/* arrays to draw into */
unsigned char zplus[BOX_SIZE][BOX_SIZE];
unsigned char zminus[BOX_SIZE][BOX_SIZE];
unsigned char xplus[BOX_SIZE][BOX_SIZE];
unsigned char xminus[BOX_SIZE][BOX_SIZE];
unsigned char yplus[BOX_SIZE][BOX_SIZE];
unsigned char yminus[BOX_SIZE][BOX_SIZE];


/* our star catalog */
struct star cat[9110];


/* writes out a pgm file from the array */
void write(char * filename,unsigned char * array)
{
FILE *fp;
fp = fopen(filename,"w");

int box = BOX_SIZE;



fprintf(fp,"P2\n");
fprintf(fp,"%d %d \n",box,box);
fprintf(fp,"%d \n",255);

int a,b;
for ( a=0; a<box; a++)
  for ( b=0; b<box; b++)
    {
    fprintf(fp,"%d \n", array[a*box+b] );
    }


}

/* initalize arrays to zero */
void clear()
{
int a,b;
for (a=0;a<BOX_SIZE;a++)
	for(b=0;b<BOX_SIZE;b++)
	{
	zplus[a][b]=0;	
	zminus[a][b]=0;	
	xplus[a][b]=0;	
	xminus[a][b]=0;	
	yplus[a][b]=0;	
	yminus[a][b]=0;	
	}
}


/* trig functions in degrees */
double sind(double theta)
{
return sin(theta*M_PI/180.0);
}

double cosd(double theta)
{
return cos(theta*M_PI/180.0);
}

/* squares a number */
double sq(double a)
{
return a*a;
}



void plot(double ra,double dec,double mag)
{

unsigned char c; // colour

int b=BOX_SIZE; // size

int x,y; // 2d coords to plot

double xx,yy,zz; // 3d vector
double l; // length of vector

/* convert to vector */
xx= cosd(dec)*cosd(ra);
yy= cosd(dec)*sind(ra);
zz= sind(dec);

/* normalise vector  */
l = sqrt(sq(xx)+sq(yy)+sq(zz));
xx /= l;
yy /= l;
zz /= l;



/* calculate colour to plot from apparent visual magnitude */
double bright =  log (5.0-mag);
if (bright > 1.0) bright = 1.0;
c = (unsigned char) (bright * 255);
//if (mag < 1.5) c= 255;

if ( (fabs(zz)>fabs(xx)) && (fabs(zz)>fabs(yy)) && (zz>0.0))

	{
	// plot in positive z plane 

	x = xx * (1.0/zz) * (b/2.0);
	y= yy * (1.0/zz) * (b/2.0);

	


	if ( (x>-b/2) && (x<b/2) && (x>-b/2) && (x<b/2) ) zplus[b/2+y][b/2+x] = c;

	}

if ( ((fabs(zz)>fabs(xx)) && (fabs(zz)>fabs(yy))) && (zz<0.0))
	{
	// plotting in negative z plane
	x = xx * (1.0/zz) * (b/2.0);
	y= yy * (1.0/zz) * (b/2.0);

	if ( (x>-b/2) && (x<b/2) && (x>-b/2) && (x<b/2) ) zminus[b/2+y][b/2-x] = c;
	}


if ( ((fabs(xx)>fabs(zz)) && (fabs(xx)>fabs(yy))) && (xx>0.0))
	{
	// ploting in positve x plane
	x = yy * (1.0/xx)* (b/2.0);
	y= zz * (1.0/xx)* (b/2.0);

	if ( (x>-b/2) && (x<b/2) && (x>-b/2) && (x<b/2) ) xplus[b/2-y][b/2-x] = c;
	}


if ( ((fabs(xx)>fabs(zz)) && (fabs(xx)>fabs(yy))) && (xx<0.0))
	{
	// ploting in negative x plane
	x = yy * (1.0/xx)* (b/2.0);
	y= zz * (1.0/xx)* (b/2.0);
		
	if ( (x>-b/2) && (x<b/2) && (x>-b/2) && (x<b/2) ) xminus[b/2-y][b/2-x] = c;
	}

if ( ((fabs(yy)>fabs(zz)) && (fabs(yy)>fabs(xx))) && (yy>0.0))
	{
	// ploting in positve y plane
	x = xx *(1.0/yy)*(b/2.0);
	y= zz *(1.0/yy)*(b/2.0);

	if ( (x>-b/2) && (x<b/2) && (x>-b/2) && (x<b/2) ) yplus[b/2-y][b/2+x] = c;
	}

if ( ((fabs(yy)>fabs(zz)) && (fabs(yy)>fabs(xx))) && (yy<0.0))
	{
	// ploting in negative y plane
	x = xx *(1.0/yy)*(b/2.0);
	y= zz *(1.0/yy)*(b/2.0);

	if ( (x>-b/2) && (x<b/2) && (x>-b/2) && (x<b/2) ) yminus[b/2-y][b/2+x] = c;
	}

}




int main( void )
{  
FILE* fp;
char line [512]; // string to read line into

char bsc[5]; // string to read number into
int bsc_num=0; // catalog number

char ra[16]; // string to read RA into
int rah ,ram; // RA hours and minutes
float ras; // RA seconds

char dec[16]; // string to read DEC into
int decsign; // sign of DEC  (north or south)
int decd, decm; // DEC degrees and minutes
int decs; // DEC seconds

char mag[16]; // string to read magnitude into
float vis_mag; // apparent visual magnitude

/* open catalog file to read */
fp = fopen("./bsc5.dat","r");


int c,t; // loop counters

/* for each star in the catalog */
for (c=0;c<9110;c++)
	{
	/* read line we don't need more than 200 chars*/
	for ( t=0;t<200;t++)
		{
		line[t] = getc(fp);
		if (line[t] == '\n') break;
		}
	if (line[t+1] == EOF) break;

	/* make sure our string is null terminated */
	line [t]=0;

	/* each line of the catalog has the same format so for each value we just read the columns that we need */

	/* catalog number (we don't use this) */
	bsc[0]=line[0];
	bsc[1]=line[1];
	bsc[2]=line[2];
	bsc[3]=line[3];
	bsc[4]=0;

	sscanf(bsc,"%d",&bsc_num);

	/* RA hours */
	ra [0]=line[75];
	ra [1]=line[76];
	ra [2]=0;
	sscanf(ra,"%d",&rah);

	/* RA minutes */
	ra [0]=line[77];
	ra [1]=line[78];
	ra [2]=0;
	sscanf(ra,"%d",&ram);

	/* RA seconds */
	ra [0]=line[79];
	ra [1]=line[80];
	ra [2]=line[81];
	ra [3]=line[82];
	ra [4]=0;
	sscanf(ra,"%f",&ras);


	/* DEC sign */
	dec[0] = line [83];
	if (dec [0] == '-' ) decsign=-1;
	else decsign = +1;

	/* DEC degrees */
	dec [0]=line[84];
	dec [1]=line[85];
	dec [2]=0;
	sscanf(dec,"%d",&decd);

	/* DEC minutes */
	dec [0]=line[86];
	dec [1]=line[87];
	dec [2]=0;
	sscanf(dec,"%d",&decm);

	/* DEC seconds */
	dec [0]=line[88];
	dec [1]=line[89];
	dec [2]=0;
	sscanf(dec,"%d",&decs);

	/* apparent visual magnitude */
	mag [0]=line[102];
	mag [1]=line[103];
	mag [2]=line[104];
	mag [3]=line[105];
	mag [4]=line[106];
	mag [5]=0;
	sscanf(mag,"%f",&vis_mag);


	/* convert to degrees */
	double dec_deg = (decd+(1.0/60.0)*decm+(1.0/3600.0)*decs)*decsign;
	double ra_deg = (rah+(1.0/60.0)*ram+(1.0/3600.0)*ras) * 15.0;

	/* sanity check the range */
	if (ra_deg > 360.0) ra_deg -= 360.0;
	if (ra_deg > 360.0) ra_deg -= 360.0;
	if (ra_deg < 0.0) ra_deg += 360.0;
	if (ra_deg < 0.0) ra_deg += 360.0;

	/* add entry to our catalog */
	cat[c].mag = vis_mag;
	cat[c].dec = dec_deg;
	cat[c].ra = ra_deg;

	}

/* clear bitmap arrays */
clear();

/* plot the stars */
for (t=0;t<9110;t++)
{
plot(cat[t].ra,cat[t].dec,cat[t].mag);
}

/* write out the results */
write("zpos.pgm",&zplus[0][0]);
write("zneg.pgm",&zminus[0][0]);
write("xpos.pgm",&xplus[0][0]);
write("xneg.pgm",&xminus[0][0]);
write("ypos.pgm",&yplus[0][0]);
write("yneg.pgm",&yminus[0][0]);


}
