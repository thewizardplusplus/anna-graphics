This is a skybox generator 

It works by reading the ascii version of the yale bright star catalog extracting the J2000 coordinates and plotting them onto 6 square bitmaps which are then output in pgm format. The coordinates are converted to degrees, then converted to a vector which is normalised the component with the largest magnitude controls which bitmap the star is rendered to the coordinates are then scaled and the brightness is calculated based on the apparent visual magnitude.

It is intended to be used to generate a night sky skybox for use in computer games to enable the player to navigate by the stars. I have include a skybox with a grid marked on it that shows the orientation of the skybox the green line represents the celestial equator and the red line zero of right assension (first point of aries). It should be possible to correctly orientate the skybox with 2 rotations, rotate the celstial equator according to the latitude and rotate zero of right assension according to longitude and time of day (UTC). The skybox is drawn using J2000 cordinates, therefore it is accurate for 1st january 2000 (at midday UTC), I have taken into account proper motion or pressession of the equinox but for a computer game background it's good for year 2000+/-25 years at least.

you will need the ascii version of the bright star catalog from here:
	http://tdc-www.harvard.edu/catalogs/bsc5.html

you compile it like this:
	gcc bsc.c -o bsc -lm

a primitive bash script which converts the output to png format using netpbm is also included.

Author is Mystic Mike (Mike Hosker)
licence is GPL v2 or at your option any later version.




 
