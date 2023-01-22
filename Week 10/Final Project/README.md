# IP System Monitor
#### Video Demo: https://vimeo.com/781678880
#### Description: IP System Monitor provides the active status of a collection of devices on an IP subnet.


# The problem

In large commercial audio visual (av) projects we are often deploying a number of varied network devices from different manufacturers onto an ip network. Once all the ip devices are online it allows us to begin the process of configuring equipment and turn a collection of individual devices into a network of devices communicating with one another. This app serves as a discovery platform that will automatically detect if these devices are on or offline and have this infoaccessable by both onsite technicians and supervisors such as project managers who may be offsite.

One of the problems faced when first deploying an av system onto a network is the network cabling infrastructure may have been done by a 3rd party contractor, the network switches from another contractor, the patching by another party, and when the network equipment is deployed and devices are unable to be detected and we there often needs to be an extensive troubleshooting process to establish the origin of the fault.

Another problem is it can be hard to get visibility of the state of the system to determine if the devices, including infrastructure, are in a suitable state for commissioning and programming staff or if a recently connected device is visible from a network perspective. If it's possible to have a live (or close to) snapshot of the current visibility of devices on the network an onsite technician can take immidiate action to resolve the issue, rather than the issue being picked up later when a programming team arrives to

If devices are assigned their ip addresses, either through a dhcp server or staticaly on the device, prior to their deployment onto the network, an active device monitor can give live updates showing when the device is successfuly deployed and is ready for programming or further configuration.


# The solution

The IP system monitor has 2 parts, a server app (python script) and a wep app (Flask). The server app reads from a list of known ip addresses entered by the user. It then pings each device on the list and records if there was a successful response or not. The result is uploaded to a database (Firebase), this process runs every 3 mins. The web app shows the list of ip addresses the user entered along with the status of the device ("online" or "not detected"). It it publicaly visible so it can be viewed by employees as well as 3rd party contractors.



# What do each of the files do?

/Server/ip.txt
Where the ip addresses to be monitored are entered. Do not leave any extra blank lines as these will read as a device with no ip address.

/Server/ping.py
run this file to start the server.
requires:
python 3.10
firebase-admin

/Server/key.json (placeholder)
this is the key for the firebase database. The contents of this file hve been deleted for security reasons

/Web Client/app.py
Flask backend to run the web app, connects to the firebase database

/Web Client/key.json
this is the key for the firebase database. The contents of this file hve been deleted for security reasons

/Web Client/static/styles.css
.css for the web app

/Web Client/templates/index.html
.html for the web app


# Design choices

programming language choices
I had a need for this app at my workplace as an Audio Visual Integrator for a particular installation about 4000kms away. I knew we were sending equipment to site shortly and I'd need to get the app loaded onto a pc ready for an installer to put into place. A week after this the equipment would be onsite and installers would be working over the weekend when I'm not online, this is why a public facing web app was so useful for this project. This gave me 1 week to make the server app and another week to make the web app, all after hours from my day job.

detect ip address or mac address
detecting devices by ip address seemed obvious as once a device can be pinged at its ip address it proves a device is in a reasonable state for further config so it was the logical choice.

There may be a benefit to having ip addresses detected by mac address for a random assignment DHCP network but for this project I decided to stick with IP address as the reference

database type/hosting choices
I wanted to utilise a free cloud hosted database service. I had also wanted to stick with SQL as I had some familiarity with it. Azure was a logical choice for SQL but I wasn't confident i could get it set up intime. In the end i chose Firebase Firestore as it seemed quick to get up and running and the documentation was comprehensive with python examples.

scripting
I had initially wanted to use HTML CSS JS for the web app however I had more confidence I could get a FLASK instance up and running in the timeframe.

website hosting choices
Initially i planned to host on Azure with the db but with the move to firestore I planned to use their project hosting. Once I got to uploading the web app I discovered I'd need to use cloud store due to the FLASK instance and would require a credit card on file and wasn't suitable. Pythonanywhere was quick to setup and given its only a single page web app seemed suitable enough. Due to the simple setup it allowed me to get thr project uploaded by the deadline.

log in/no log in
As there is no personal or secure information presented in the HTML it seemed like overkill and needlessly comples to have the app behind a login

# Summary
The app has delivered the neccecary functionaity for the mean time, it has already been deployed and working as intended. I have also modified to make a local only version which I have also been using.

There are other opportunities to improve from here, using a different stack and some attention to the UI are the first areas I look at.



v1.0.1
14/12/22
