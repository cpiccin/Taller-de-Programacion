# Threads

Se utiliza la implementacion de 
- sockets `hands-on-sockets-in-cpp` por el dipa bajo licencia GPL v2. Repo https://github.com/eldipa/hands-on-sockets-in-cpp.git
- thread y queue `hands-on-threads` por el dipa bajo licencia GPL v2. Repo https://github.com/eldipa/hands-on-threads.git

### Sobre uso de pop y push bloqueante o no-bloqueante
Para el gameloop uso `try_push()` y `try_pop()` porque las operaciones dentro del loop deben ser no-bloqueantes. Si fuesen bloqueantes las iteraciones en el _mundo del juego_ se verian afectadas por el tiempo adicional del bloqueo.

Para los threads sender y receiver de cada cliente que se conecta, se utilizan las operaciones bloqueantes `pop()` y `push()` porque su proposito es quedarse esperando por algun mensaje que se reciba o se tenga que enviar, para mantener una sincronizacion y orden.

![diagrama](https://github.com/user-attachments/assets/841e3516-f449-4cd0-b607-c495aaf94553)


**nota**: ~~me pasa valgrind, no hay memleaks pero hay open file descriptors, vi que puede ser un falso positivo de valgrind pero no se porque no llegue a correrlo en el sercom~~ pasa 100% en sercom
 
