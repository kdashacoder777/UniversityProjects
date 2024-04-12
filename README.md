If you use Windows 10+ please will install WSL:
<https://learn.microsoft.com/ru-ru/windows/wsl/instal/>

Requirements for build:
```
$sudo apt-get update
$sudo apt-get install gdb
$sudo apt-get install gcc
sudo apt install libomp-dev
$sudo apt-get install cmake
$sudo apt-get install build-essential
$sudo apt-get upgrade
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

MatrixVectorMultiplication:
--------------
|Razmer obektov|Posledovatelnyj algoritm (vremya) ms|2 processa (vremya) ms|2 processa (izmenenie) ms|4 processa (vremya) ms|4 processa (izmenenie) ms|8 processov (vremya) ms|8 processov (izmenenie) ms|16 processov (vremya) ms|16 processov (izmenenie) ms|
| ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      |
|2000      |25.4662   |14.6684   |10.7978   |10.401    |15.0652   |6.35378   |19.1124   |18.7857   |6.68048   |
|5000      |160.503   |75.8162   |84.6863   |69.5018   |91.0008   |74.5242   |85.9783   |73.6909   |86.8116   |
|10000     |513.376   |291.281   |222.095   |227.728   |285.647   |165.342   |348.033   |161.334   |352.041   |
|15000     |1048.72   |609.983   |438.732   |474.762   |573.953   |352.043   |696.673   |363.046   |685.67    |
|30000     |4464.93   |2487.46   |1977.47   |1630.36   |2834.57   |1379.66   |3085.27   |1443.59   |3021.34   |

selectionSort:
--------------
| Razmer obektov | Posledovatelnyj algoritm (vremya) ms | 2 processa (vremya) ms | 2 processa (izmenenie) ms | 4 processa (vremya) ms | 4 processa (izmenenie) ms | 8 processov (vremya) ms | 8 processov (izmenenie) ms | 16 processov (vremya) ms | 16 processov (izmenenie) ms |
|----------------|--------------------------------------|------------------------|---------------------------|------------------------|---------------------------|-------------------------|----------------------------|--------------------------|-----------------------------|
| 50000          | 2345.62                              | 1374.08                | 971.534                   | 1242.84                | 1102.78                   | 1017.66                 | 1327.96                    | 24192.1                  | -21846.5                    |
| 100000         | 9304.64                              | 5460.44                | 3844.2                    | 4788.96                | 4515.68                   | 4480.91                 | 4823.73                    | 49054.8                  | -39750.2                    |
| 150000         | 21687.9                              | 12641.7                | 9046.21                   | 11197.2                | 10490.7                   | 13198.1                 | 8489.77                    | 75894.1                  | -54206.2                    |
| 200000         | 37890.5                              | 22683.6                | 15207                     | 19355.4                | 18535.2                   | 17675.7                 | 20214.9                    | 101316                   | -63425.1                    |
| 300000         | 84201.3                              | 49400.5                | 34800.8                   | 43936.3                | 40264.9                   | 39469.1                 | 44732.2                    | 157830                   | -73628.9                 

quickSort:
----------
|Razmer obektov|Posledovatelnyj algoritm (vremya) ms|2 processa (vremya) ms|2 processa (izmenenie) ms|4 processa (vremya) ms|4 processa (izmenenie) ms|8 processov (vremya) ms|8 processov (izmenenie) ms|16 processov (vremya) ms|16 processov (izmenenie) ms|
| ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      | ---      |
|50000      |8.31873   |4.77157   |3.54716   |3.94785   |4.37089   |4.47179   |3.84695   |6.01971   |2.29902  |
|100000     |17.7858   |9.47261   |8.31314   |7.93089   |9.85486   |10.1507   |7.63503   |22.5244   |-4.73861 |
|150000     |27.602    |15.0831   |12.5189   |13.8123   |13.7897   |19.4483   |8.15367   |31.7637   |-4.16168 |
|200000     |42.7568   |18.9001   |23.8567   |16.1968   |26.5599   |20.1583   |22.5985   |20.3879   |22.3688  |
|300000     |60.4954   |31.0177   |29.4777   |27.9667   |32.5287   |39.4943   |21.0011   |39.1881   |21.3073  |

mergeSort:
----------
| Razmer obektov | Posledovatelnyj algoritm (vremya) ms | 2 processa (vremya) ms | 2 processa (izmenenie) ms | 4 processa (vremya) ms | 4 processa (izmenenie) ms | 8 processov (vremya) ms | 8 processov (izmenenie) ms | 16 processov (vremya) ms | 16 processov (izmenenie) ms |
|----------------|--------------------------------------|------------------------|---------------------------|------------------------|---------------------------|-------------------------|----------------------------|--------------------------|-----------------------------|
| 500000         | 10.4701                              | 5.61563                | 4.85443                   | 5.85461                | 4.61545                   | 6.59503                 | 3.87504                    | 11.8729                  | -1.4028                     |
| 100000         | 21.254                               | 8.85578                | 12.3982                   | 8.29504                | 12.9589                   | 8.71109                 | 12.5429                    | 22.5467                  | -1.29275                    |
| 150000         | 27.3529                              | 16.9382                | 10.4147                   | 13.6887                | 13.6643                   | 20.308                  | 7.04488                    | 32.1928                  | -4.83986                    |
| 200000         | 42.6178                              | 17.3314                | 25.2864                   | 18.1485                | 24.4693                   | 19.1455                 | 23.4723                    | 20.2123                  | 22.4055                     |
| 300000         | 62.3076                              | 31.4402                | 30.8674                   | 30.9497                | 31.3579                   | 34.2598                 | 28.0478                    | 39.4482                  | 22.8595                     |
