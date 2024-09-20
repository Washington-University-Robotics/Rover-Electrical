# Rocket M2s

To connect wirelessly across a large distance (1-2km) we are using Ubiquiti Rocket M2s for radios, along with Ubiquiti antennas. The datasheet for the Rocket M2s is included in this directory. They use 2.4 GHz frequency for comms, and have a variable bandwidth of 20-40 MHz. The competition rules state that we cannot have a bandwidth of more than 22 MHz at this frequency, so we will be limiting it to 20 MHz in the Rocket M2 settings.

## Setup

By default, the Rocket M2s broadcast an admin interface on `192.168.1.20`. The default username and password for this admin interface is:

- Username: `ubnt`
- Password: `ubnt`

For simplicities sake, we currently do not change these credentials. We do, however, change the IP. Once you have logged in to the admin page, you shoudl see a screen like this:

[image of base admin interface]

To change the IP of the Rocket, we click on the [Networking?] tab. You should be greeted with a screen like this:

[networking options menu]

At the bottom, we see the broadcasted IP of the Rocket. Change that to something else. Currently, we have the Rockets labeled with tape. Ensure you are connecting to the correct one and assigning the correct IP. It can be confusing if the IPs get switched.

[picture of the IP selection highlighted]

To change the bandwidth, we look a bit above the IP settings, and look for the [Bandwidth?] setting. By default, this is set to auto (will pick between 20-40 MHz). We need to set this to 20 MHz only in order to comply with competition standards. 

[picture of the dropdown for the bandwidth setting]

## Individual Rocket Setup

Now that we know how to configure the Rockets, we need to specify how to select the proper settings for each Rocket.

__Base Station__
For the base station the settings are as follows:

- [Type?]: Access Point
- SSID: Rover
- Security: WPA2 PSK Auth
- Password: password

__Rover__
For the Rover station the settings are as follows:

- [Type?]: Station
- SSID: Rover
- Security: WPA2 PSK Auth
- Password: password