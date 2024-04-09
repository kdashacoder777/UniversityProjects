If you use Windows 10+ please will install WSL:
<https://learn.microsoft.com/ru-ru/windows/wsl/instal/>

Requirements for build:
```
$sudo apt-get update
$sudo apt-get upgrade
$sudo apt-get install gdb
$sudo apt-get install gcc
$sudo apt-get install build-essential
```

Install OMP library:
```
$sudo apt install libomp-dev
```

Then, you can build your project:)

The experiment was running on an 8-thread laptop
================================================
Results of run:
--------------

|Razmer obektov|Posledovatelnyj algoritm (vremya) ms|2 processa (vremya) ms|2 processa (izmenenie) ms|4 processa (vremya) ms|4 processa (izmenenie) ms|8 processov (vremya) ms|8 processov (izmenenie) ms|16 processov (vremya) ms|16 processov (izmenenie) ms|
| ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      |
|2000      |25.4662   |14.6684   |10.7978   |10.401    |15.0652   |6.35378   |19.1124   |18.7857   |6.68048   |
|5000      |160.503   |75.8162   |84.6863   |69.5018   |91.0008   |74.5242   |85.9783   |73.6909   |86.8116   |
|10000     |513.376   |291.281   |222.095   |227.728   |285.647   |165.342   |348.033   |161.334   |352.041   |
|15000     |1048.72   |609.983   |438.732   |474.762   |573.953   |352.043   |696.673   |363.046   |685.67    |
|30000     |4464.93   |2487.46   |1977.47   |1630.36   |2834.57   |1379.66   |3085.27   |1443.59   |3021.34   |
