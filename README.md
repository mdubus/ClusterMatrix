# ClusterMatrix

An electronic-project made by 3 42-students for the 42-students. 

This project took us 6 months from the specifications to the final product. 

Its aim is to allow students to find easily free places to work alone or in small groups in the Clusters.

The project is now at the entrance of the school and use by the students daily. 

## Final Product

![alt text](https://github.com/mdubus/ClusterMatrix/blob/master/img/cluster-matrix.jpg)

## Usage

### Clusters

3 buttons allows the student to switch between cluster 1, 2, and 3.

Places in the Clusters are represented by colors : 

- Blue : available
- Red : unavailable

### Places

Small groups can find places next to each other thanks to 4 buttons 'places'.

For example, if 4 students wants to work with each other they can press the button '4'. The places are represented with colors : 
- Blue : this place is available and there are 3 other places available next to it. This place is recommended
- Orange : this place is available but there isn't 3 other places available next to it. This place is not recommended
- Red : this place is unavailable

This algorithm takes in consideration the orientation of the Cluster Rows and Computer Screens.

### Moving led

A led is walking around the clusters, to show us if the information is up-to-date. 
If the led is green, the information is up-to-date. If it's orange, it is not. 

### Bonus

- Loading screen
- 'Konami Code' (enable a specific effect)
- A dip switch allows us to select a current cluster or to switch between the clusters every 30seconds

## Hardware

The constraint was to code the software on a PIC32MX. The Raspberry Pi is only here to provide us the wifi and the server. 

- Power Supply (5V 8A)
- Led Stripes (WS2812B)
- Raspberry Pi Zero W
- Capacitors
- More leds
- Fuse
- Inductor
- Connector RJ11
- Connector DC
- Connector Raspberry
- Resistor
- Dip Switch
- Power Switch
- Shift Register Parallel / Serial
- Shift Register Serial / Parallel
- Voltage Regulator
- Pic 32MX

## How it works

- The Raspberry is connected to the 42-school API via wifi. 
- Every 30 seconds, the PIC32 asks the Raspberry for fresh data. 
- The Raspberry transforms the data in a serial of 0 and 1, and send it to the PIC32. 
- The PIC32 stores the data on a Matrix.
- Every time a user press a 'cluster' button, the PIC32 pick the correct data on the Matrix. 
- Every time a user press a 'place' button, the PIC32 applies an algorithm and display the result. 


## Final Mark

`121 / 100`

And the satisfaction to have made from start to end a product used every day by the students :)
