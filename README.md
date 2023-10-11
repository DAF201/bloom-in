# Will be take over by this one after I finished I guess

https://github.com/DAF201/ClearSky

# bloom-in

## What is this?

my new toy to connect two pcs in two different private networks (which is basically some sort of "Implementation" of ["blur-in"](https://github.com/DAF201/blur-in))

About protocol, see [this](https://github.com/DAF201/bloom-in/tree/main/protocol)

### Important things to know about

1. DON'T USE IT FOR PRODUCTION ENV, the protocol is not encrypted at all (it is not even binary)

2. The protocol is UDP like, it may miss some messages/commands

3. There are many better solutions for file transportation than this toy existing in the world

4. The performance of it follows "Buckets effect", if one pc is poor, the other one is good, the over all will perform poorly

5. The server is designed for small number of client to use at same time

---

09/15/22

<b>I was starting with python but now it becomes a C++ project?<b>

09/26/22

<b>I am kind of under weather... And I am damning busy

(I to stop for a while to catch up my math class now...)

10/02/22
  
Still super busy... Damn it  

10/04/22

Worked, sort of (Sorry I am working in lab, the photo quality is not that good, and the screen and camera are dirty)
  
10/10/22

damn it, my discrete math is comming

damn it, VSC blowed up.

10/12/22

sort of working, still some bugs that cuase the server to close the connection... But I don't even know how it happened...
  
fixed long string printing or execution...(sort of...don't use it to print something super long like "ipconfig /all" I will suggest...)
  
![](https://github.com/DAF201/bloom-in/blob/main/images/test01.png)
![](https://github.com/DAF201/bloom-in/blob/main/images/test02.png)

10/19/22

the weather goes all the way down from somewhere like 30C to 3C... Damn are you sure this is the weather Texas should have?

10/23/22

trying to make some sort of FTP protocol...

10/26/22

I am sorry for being an idiot. I tried so many ways but I still cannot fix the packages losing issue with File transportation...

![](https://github.com/DAF201/bloom-in/blob/main/images/Screenshot%20(138).png)

10/28/22

I ended up with http to transport file...

11/01/22

the first release is ready, file transportation is up.

11/04/22

I was trying to use this as a port to reach company's other pcs at begining but it don't looks like it can lol, cause it cannot enter password. 

---
  
I managed to make it worked, stable connection between two different machine in two different private network without VPN or NAT. (But currently I haven't make any command except 'exit', and the target_id were hard-coded for test)
  
![](https://github.com/DAF201/bloom-in/blob/main/images/A76B9DE1-EC91-4E55-B9A0-CB426166582D.jpg)
![](https://github.com/DAF201/bloom-in/blob/main/images/B4EA362E-45F4-4F80-BF2A-D5812E548FE8.jpg)
  
---

testing, not stable yet, but sort of working... I will upload the client after it become more stable

Below are screenshots the prototype, already removed

![](https://github.com/DAF201/bloom-in/blob/main/images/00EA7351-CAC0-4091-9B6F-6C1F4640A0AB.jpg)

![](https://github.com/DAF201/bloom-in/blob/main/images/1CED67C3-25CB-451D-854A-417D529C4D11.jpg)

