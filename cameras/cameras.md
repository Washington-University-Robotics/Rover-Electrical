# Cameras

For cameras, we have a few main concerns:

1. Front-facing, high resolution cameras for seeing the way forward, pathfinding
2. Wide angle cameras to get a wide view of our surroundings in all directions
3. An Arm POV camera to enable autonomous arm movements without needing to do weird and complicated stuff by using the main-chassis cameras
4. A 460 degree camera for the underside to use for looking at the ground closely and watching the auger in motion

The strategy we will use is to buy discrete USB cameras and connect them all to a USB hub, which then connects to the main computer aboard the Rover. Other options would include picking camera sensors and developing our own camera system, but for the moment, we want to create a working product, and we can think about handcrafting every component later.

The front-facing cameras have already been purchased. There is the Zed 2, and [another camera that I don't know much about while writing these docs]. Both cameras have a USB-A output, and can plug into a hub or directly into the main compute. The other cameras are as of yet undecided.

## Requirements
The main requirements for each set of cameras (Arm POV, Wide-angle array) is as follows:

_Arm POV_
- Depth mapping (either 2 cameras that can be used to depth map, or a single depth mapping cam)
- High Resolution
- Small and compact, not a weird shape

_Wide Angle Array_
- Needs to be able to see in 360 degrees around the rover (not vertically, just L/R F/B)
- Needs to be high enough resolution to be able to see the surrounding area with relatively high quality
- Small and compact, not a weird shape

## Possible Solutions

### Wide-Angle Array
There are multiple options to choose from, but our primary focus is on a small USB camera based on Sony sensor technology, seen [here](https://www.amazon.com/4K-Cameras-No-Distortion-Support-Windows/dp/B089QHRH93?th=1). These present a few options, both with provided cases or with just the board, and in 90°, 100°, and 170° variants. All variants run at 4k/30fps. They include other features such as auto-white balancing, compression, which can be seen on the product page on Amazon.

If we use the 170° option, there will be some fishlens effect on the image that will have to be accounted for in the control software. The 100° and 90° options do not have any distortion.


### Arm POV

There are two main ways to do the depth mapping. IR depth-mapping is a popular method, usually referred to as ToF (Time of Flight), but can suffer accuracy during the day. Using a stereo camera setup and AI to do the depth mapping is another popular solution, but this can cost more compute than just recieving the raw pixel-distance data. 

If IR depth-mapping is chosen, we will need two separate cameras. One for the depth-mapping and one for the actual images. These will be slightly offset from each other, since the sensors will be in different places. 

If a stereo and AI setup is chosen, the software team will need to figure out how to do the depth mapping themselves using just the stereo cameras. The cameras will be at high resolution so there will be plenty of data.