from multiprocessing import Process, Queue

def origem(fila1):
  for i in range(10):
    msg = 'Teste ' + str(i)
    # envia mensagem para a ponte pela fila 1
    fila1.put(msg)
    print('Mensagem enviada:', msg)

def ponte(fila1, fila2):
  for i in range(10):
    msg = fila1.get()
    # recebe mensagem na fila 1
    # reenvia mensagem na fila 2
    print('Mensagem encaminhada:', msg)
    fila2.put(msg)

def destino(fila2):
  for i in range(10):
    msg = fila2.get()
    # recebe mensagem na fila 2
    print('Mensagem recebida:', msg)
      


if __name__ == '__main__':
  fila1 = Queue()
  fila2 = Queue()
  o = Process(target=origem, args=(fila1,))
  p = Process(target=ponte, args=(fila1,fila2))
  d = Process(target=destino, args=(fila2,))
  o.start()
  p.start()
  d.start()

  processos = [o,p,d]
  for processo in processos:
    processo.join()

  for processo in processos:
    processo.terminate()
  # executa os processos
  # aguarda conclusão
  # libera as filas