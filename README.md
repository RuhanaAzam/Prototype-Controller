



This is a communication unit which establishes a manager (master/controller)
and multiple worker units. We use multi threading to run multiple Servers&Clients
allowing for bi directional flow of information/data over a TCP network.

We use the ASIO C++ library for some higher level functions for handling sockets, however
we manually control threads and avoid use of ASIO's asynchronous operations.


Compilation for manager:
> ./managerCompile

Compilation for worker:
> ./workerCompile




<img align="Left" width="400" height="500" src="diagrams/OneWorkerVisualization.jpg">

<img align="Right" width="400" height="500" src="diagrams/HighLevelVisualization.jpg">

