If you use Windows 10+ please will install WSL:
<http://example.com/](https://learn.microsoft.com/ru-ru/windows/wsl/instal/)>

Requirements for build:
```
$sudo apt-get update
$sudo apt-get upgrade
$apt-get install gdb
$sudo apt-get install gcc
$sudo apt-get install build-essential
```

Install OMP library:
```
$sudo apt install libomp-dev
```

Then, you can build your project:)

Results of run:

Razmer obektov;Posledovatelnyj algoritm (vremya);2 processa (vremya);2 processa (izmenenie);4 processa (vremya);4 processa (izmenenie);8 processov (vremya);8 processov (izmenenie);16 processov (vremya);16 processov (izmenenie);
2000;4.813;2.99769;1.81531;1.57346;3.23954;2.75618;2.05682;5.61216;-0.799156;
5000;26.5486;16.8916;9.65703;9.3422;17.2064;11.1955;15.3531;13.5933;12.9553;
10000;104.494;56.2283;48.2662;31.8155;72.6789;24.1693;80.3252;25.4926;79.0019;
15000;237.519;124.811;112.708;71.8748;165.644;53.0194;184.499;55.5419;181.977;

