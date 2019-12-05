# drones-route-calculation

This project is to compute delivery sequences for drones that deliver parcels to customers. Each batch of deliveries is described by a `.tsv` file that has one row of numbers for each package that has to be delivered.

## Stage 1: Data read

This stage will read the file into the dataset. Once the entire dataset has been read, the program should print the total number of data lines that were read, the first and last of the input records, and the total of the package weights. Sample output:

  `
   S1, total data lines: 5
   S1, first data line : x= 150.6, y=-185.2, kg=2.50
   S1, final data line : x= -27.8, y= 312.6, kg=1.95
   S1, total to deliver: 18.61 kg
  `

## Stage 2: Delivery

This stage will compute the delivery sequence for the drones (return trip included), based on specs:

`Drones are battery powered, and can carry up to 5.8 kilograms each in addition to the 3.8 kilogram weight of the drone itself. When the drone is carrying a payload of w kilograms, a fully-charged battery pack allows the drone to safely fly a total of 6300/(3.8 + w) meters. That is, an unladen drone can safely travel a total of 6300/3.8 = 1657.9 meters, whereas a fully laden drone can only safely fly 6300/(3.8 + 5.8) = 656.3 meters. The drones fly at a constant speed of 4.2 meters/second, and always fly in a straight line from one specified location to another.`

The drone will change battery if the previous one's capacity is not enough for the next trip. Default departing location is assumed to be (0,0). Example output:

`
S2, package= 0, distance= 238.7m, battery out=23.9%, battery ret=14.4%

S2, change the battery

S2, package= 1, distance= 513.7m, battery out=64.8%, battery ret=31.0%

S2, change the battery

S2, package= 2, distance= 60.8m,  battery out= 7.8%, battery ret= 3.7%

S2, package= 3, distance= 199.0m, battery out=30.0%, battery ret=12.0%

S2, change the battery

S2, package= 4, distance= 313.8m, battery out=28.6%, battery ret=18.9%

S2, total batteries required: 4

S2, total flight distance=2652.0 meters, total flight time= 631 seconds
`

## Stage 3: Arrangement

To make better use of the batteries, the program is now modified so that after each delivery has been completed, all of the remaining undelivered packages are considered in turn, and if any of them can be delivered using the current battery, that delivery is carried out next. Default location is used. Example output:

`
S3, package= 0, distance= 238.7m, battery out=23.9%, battery ret=14.4%

S3, package= 2, distance= 60.8m,  battery out= 7.8%, battery ret= 3.7%

S3, package= 3, distance= 199.0m, battery out=30.0%, battery ret=12.0%

S3, change the battery

S3, package= 1, distance= 513.7m, battery out=64.8%, battery ret=31.0%

S3, change the battery

S3, package= 4, distance= 313.8m, battery out=28.6%, battery ret=18.9%

S3, total batteries required: 3

S3, total flight distance=2652.0 meters, total flight time= 631 seconds
`
## Stage 4: Set departing location

This stage will further ultilize the use of batteries, by setting the departing location to be the most efficient, which is the centroid. The centroid can be computed using the mean of x-coordinates and the mean of y-coordinates. Then the rest will act the same as stage 3, but with a new starting point. Example output:

`
S4, centroid location x= 29.4m, y= 174.1m

S4, package= 0, distance= 379.2m, battery out=37.9%, battery ret=22.9%

S4, package= 2, distance= 136.6m, battery out=17.6%, battery ret= 8.2%

S4, change the battery

S4, package= 1, distance= 337.6m, battery out=42.6%, battery ret=20.4%

S4, package= 3, distance= 89.1m,  battery out=13.4%, battery ret= 5.4%

S4, change the battery

S4, package= 4, distance= 149.8m, battery out=13.7%, battery ret= 9.0%

S4, total batteries required: 3

S4, total flight distance=2184.5 meters, total flight time= 520 seconds
`

*Project specs are taken from The University of Melbourne, Department of Computing and Information Systems, 2019*
