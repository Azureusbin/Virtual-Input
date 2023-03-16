# Virtual Input

Virtual Input is a unreal engine plugin，this plugin can send dummy input device events to engine, And no physical contact with input device is required.

------



## Overview

Right click blueprint viewport and searching 'Virtual Input', then you can see all blueprint node.

![蓝图节点分类](imgs/Virtual Input/蓝图节点分类-16789704874271.png)



------



## Getting Started

- Step 1


​		Make sure 'Virtual Input' was loaded in your engine.

​		![](imgs/Virtual Input/image-20230316195416614-16789704913873.png)

​	

- Step 2

​		Find some reasonable location to create your own blueprint. Then you can place virtual input node, to achieve your idea.

​		

------



##  Example

This section will teach you implement some common functions.



###  Simulate right mouse button click

![image-20230316200631903](imgs/Virtual Input/image-20230316200631903-16789704951825.png)

Trigger by 'Right Click' Event, and the whole click took 0.2 seconds.





###  Simulate Left Mouse Button Double Click

![image-20230316200833983](imgs/Virtual Input/image-20230316200833983-16789704983477.png)

Use node 'Dummy Mouse Button Clicked', check off 'Double Click'.





###  Simulate dragging something move 100 coordinates to the right

![image-20230316201050396](imgs/Virtual Input/image-20230316201050396-16789705007329.png)

Assume that the current mouse is on the something to be dragged. Trigger event 'Drag Something', then you will see that it will drag to the right.





###  Move cursor to specify location

![image-20230316201404623](imgs/Virtual Input/image-20230316201404623-167897050271411.png)

This plugin provide two option to finish that job, using absolute coordinate or viewport coordinate.





###  Simulate key input

![image-20230316201615480](imgs/Virtual Input/image-20230316201615480-167897050452513.png)

There are two ways to achieve this. They are equivalent.

It is worth noting that 'Repeat' should not be checked when pressed key. Do not check up 'Repeat' unless you need to repeatedly trigger the pressed event.



------

##  Update plan

- To support more unreal engine version
- Theoretically supports all platforms, but has not been tested.
