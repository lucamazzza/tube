# Problema dei tubi

## Descrizione del problema

Il progetto consiste nella risoluzione di un problema di ottimizzazione per quanto riguarda una fabbrica di cioccolato.

La suddetta fabbrica presenta una tanica di cioccolato (*root*) dalla quale partono diverse tubature che portano il 
cioccolato alle stazioni di produzione; queste tubature sono interconnesse da dei giunti (*nodes*) che periodicamente
devono essere manutenuti, e questo richiede del tempo.

Sono però disponibili dei giunti (*nodes*) di ricambio che azzerano il tempo di manutenzione.

Si deve quindi trovare quali giunti nella diramazione di tubi è ottimo cambiare per ottenere il minor tempo possibile
per l'inizio della produzione.

## Input

La prima riga contiene due numeri interi $N$, $C$; il primo rappresenta il numero totale di giunti presenti nel sistema,
mentre il secondo rappresenta il numero di ricambi disponibili.
Le righe successive sono composte dal parametro $Tn$(tempo di riparazione) e $Pn$(nodo parante). 

```
N C
t0 p0
t1 p1
 ...
ti pi
```

### Vincoli

- Intero $1 \le N \le 10000$
- Intero $0 \le C \le 100$
- Intero $0 \le T_i \le 10^4$
- Un solo valore $P_i = -1$ mentre per tutti gli altri $0 \le P_i \lt N$
- Esiste sempre una sequenza che da i conduce alla tanica principale
- Gimmy Donka di un numero illimitato di UmpaZumpa in grado di effettuare le operazioni e manutenzione in parallelo

## Output

- Un singolo valore intero che rappresenta il minimo tempo entro il quale l'ultima stazione puo iniziare la produzione

## Requisiti

- Elaborare una soluzione che sfrutti la programmazione dinamica

## Soluzione

```
procedure minimize_time(node)
  if number of childs == 0 then
    memorized_times[node][0] = maintenance_time[node] 
    for each not changed do
        memorized_times[node][change] = 0
    end for
    return
  end if
  
  for each node in subtree do
    v = n-th adjacent node
    minimize_time(v)
    current_trial_iteration[]
    
    for each change do
      current_trial_iteration[change] = infinite 
    end do

    for each change do
      for each n-th change made do
        current_trial_iteration[change] = min(current_trial_iteration[change], max(memorized_times[v][(n-th change)], mememorized_times[node][change - (n-th change)]))
      end do
    end do

    for eache change do
      mem[node][change] = current_trial_iteration[change]
    end do
  end do

  current_trial_iteration[]
  current_trial_iteration[0] = maintenance_time[node] + memomrized_times[node][0]
  
  for each change do
    current_trial_iteration[change] = min(maintenance_time[node] + memomrized_times[node][change], memomrized_times[node][change - 1])
  end do

  for eache change do
    mem[node][change] = current_trial_iteration[change]
  end do
end procedure
```

### Statistiche di tempo

- Tempo medio: $0.000164$ s.
- Tempo min: $0.000136$ s.
- Tempo max: $0.000200$ s.

### Statistiche di spazio

## Conclusione

### Soluzioni alternative

Abbiamo provato ad usare un algoritmo DFS ma abbiamo trovato questo metodo molti piu semplice e veloce da applicare.
