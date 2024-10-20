# ie0217-proyecto
Proyecto para el curso IE-0217 II-2024 correspondiente a un sistema de gestión utilizado por los agentes de atención al cliente en ventanillas de una entidad bancaria.

## Fase 1: Investigación

En esta sección se definen los conceptos, funcionamiento y caracteristicas de las partes de un sistema de gestión bancaria que serán las bases sobre las cuales se desarrollarán las distintas funcionalidades, implementaciones y diseño de nuestro programa. 

## Préstamos

Antes que nada es importante definir que es un préstamo garantizado y no garantizado:

## Préstamos garantizados 

Es aquel que se otorga en base a algún tipo de garantía a modo de respaldo, que puede ser una propiedad o un bien material ó un aval financiero como un depósito bancario, acciones o similares. 

El punto es que la garantía se usa para asegurarse que el prestamista recupere el dinero prestado en caso de que el deudor no pueda pagar. 

Este tipo de préstamos tienen una tasa de intéres más baja que los no garantizados y plazos de pago más largos, lo cual hace que los pagos mensuales sean menores. 


## Préstamos no garantizados 

Para solicitar estos préstamos no se requiere de ninguna garantía más que la solvencia del deudor para pagar, pero presenta un riesgo para el prestamista ya que no hay forma de asegurarse de que el deudor vaya a pagar. Por este mismo riesgo para el prestamista estos préstamos suelen pactarse con periodos de pago más cortos y a una tasa de intéres mucho mayor. 


Teniendo esto claro pasamos a explicar cada tiṕo de préstamo:


## Préstamos personales

Es un tipo de préstamo **no garantizado** en el que se presta una cantidad específica de dinero a una persona, con la promesa de devolverlo en cuotas regulares. Es comúnmente utilizado para gastos personales, como la compra de electrodomésticos, viajes o consolidación de deudas. La información requierida para estimar el pago de este tipo de préstamos es:

- **Monto solicitado:** Cantidad de dinero que se desea pedir prestado

- **Plazo:** Período de tiempo en el que se pagará el préstamo (en meses)

- **Tasa de interés:** Porcentaje anual que se aplica al monto del préstamo


## Préstamo prendario

Es un préstamo que está **garantizado** por un bien mueble, como un vehículo o joyas. En caso de incumplimiento de pago, el banco puede tomar posesión del bien en garantía. 

Como se mencionó antes estos tiene una tasa de interés más baja que los no garantizados porque hay una garantía física de que el deudor no incumplirá los pagos. 

La información que se requiere para estimar el pago es la misma que el préstamo personal, pero se debe asegurar que el bien que se ha dado como garantía tenga el mismo valor o superior al valor del préstamo. 


## Préstamo hipotecario

Es un préstamo que se **garantiza** con una propiedad inmueble, como una casa o terreno. Se utiliza comúnmente para la compra, construcción o remodelación de bienes raíces. Para calcular el pago de este tipo de préstamos se requiere:

- **Valor de la propiedad:** Valor estimado del inmueble que servirá como garantía

- **Monto solicitado:** Cuánto dinero se quiere pedir prestado para la compra o construcción

- **Plazo:** Tiempo en el que se pagará el préstamo (suele ser más largo que otros préstamos, por ejemplo, 15 a 30 años)

- **Tasa de interés:** Porcentaje aplicado sobre el monto del préstamo, que puede ser fija o variable


## ¿Cómo se calculan los montos de las cuotas de pago y los intereses?

### Cuotas mensuales

El pago de cada cuota mensual para cualquiera de los préstamos anteriores se calcula en base a la siguiente fórmula:

$$C=\frac{P\cdot i\cdot (1+i)^n}{(1+i)^n-1}$$

Donde:

- $C$ es la cuota mensual

- $P$  es el monto del préstamo 

- $i$ es la tasa de interés mensual

- $n$ es el numero total de meses de pago

### Intereses

Existen dos tipos de intereses, **fijos** y **variables**. Si la tasa de interés es fija en el plazo del préstamo, significa que este será constante a lo largo de la duración del préstamo. Este de define en un plazo anual y en la fórmula anterior se ingresa el mensual, entonces el valor de interés que va en la fórmula anterior es:

$$i=\frac{i_A}{12}$$

Donde $i_A$ es la tasa de interés anual que normalmente se define como un porcentaje, por ejemplo $15\%$ ó $12\%$. Ahora bien si el interés es variable significa que este valor cambia en base al saldo pendiente del préstamo en cuestión, de la siguiente manera:

$$i_V=\text{Saldo pendiente del préstamo} \times i$$

Donde $i_V$ es la tasa de interés variable en cada cuota, e $i$ es la tasa de interés que se definió para la duración de todo el préstamo. Entonces si se tiene una tasa de interés variable en un préstamo su pago en cada cuota se calcula así:

$$C=\frac{P\cdot i_V\cdot (1+i_V)^n}{(1+i_V)^n-1}$$

Todos lo préstamos pueden tener tasas de intéres variable o fija. 


## Cuentas de Ahorros

Es una cuenta bancaria que permite a una persona depositar dinero para ahorrarlo y ganar intereses sobre el saldo. Las cuentas de ahorro suelen tener menos requisitos que otros tipos de cuentas y son accesibles para la mayoría de las personas. La información requerida para abrir una cuenta de ahorro comúnmente es:

- Identificación personal (cédula o pasaporte)

- Comprobante de domicilio

- Monto mínimo de apertura, dependiendo del banco

- Tasa de interés sobre saldo promedio

Esta tasa de interés en las cuentas de ahorro se calcula diariamente por medio de la siguiente fórmula:

$$I_D=\frac{\text{Saldo al final del día}\times i}{365}$$

Donde $i$ es la tasa de interés de la cuenta de ahorro e $I_D$ es la el valor diario de interés que se suma a la cuenta. 

## Certificado de depósito a plazo (CDP)

Es un tipo de inversión en la que se deposita una cantidad de dinero durante un período fijo, y el banco paga intereses sobre el monto al final del plazo. El dinero no puede retirarse antes de la fecha de vencimiento sin incurrir en penalizaciones. La información requerida para abrir un CDP es:

- Identificación personal (cédula o pasaporte)

- Monto mínimo de inversión, que varía según el banco

- Plazo del depósito, que puede ser de meses o años

- Tasa de interés pactada

Se puede calcular el monto de interés ganado al vencimiento del CDP por medio de la siguiente fórmula:

$$I=P\cdot i\cdot t$$

Donde:

- $I$ es el interés ganado

- $P$ es el monto del CDP

- $i$ es la tasa de interés anual

- $t$ tiempo de duración del CDP, en años 

Cabe mencionar que $i$ se calcula igual que como se explicó para los préstamos. 


## Reportes de transacciones

Normalmente cada transacción tiene información distinta en sus reportes, pero hay varios datos básicos que debe incluir cualquier reporte:

- ID de Transacción: Identificador único

- Tipo de Transacción: Depósito, retiro, transferencia, abono a préstamo

- Monto: Importe de la transacción

- Cuenta de Origen: Número o ID de la cuenta que origina la transacción

- Cuenta de Destino (si aplica): En caso de transferencias o abonos

- Cliente Asociado: Número de cédula o ID del cliente que ejecutó la transacción

Ahora bien hay datos específicos que se deben tener para cada tipo de transacción:

### Depósitos y Retiros

- Saldo anterior

- Saldo actual después de la transacción

### Transferencias

- Nombre del cliente receptor de la transferencia

### Abonos a Préstamos

- ID del préstamo

- Cuota pagada

- Aporte al capital

- Aporte a los intereses

- Saldo restante del préstamo

### Pago al vencer un CDP

- ID del CDP

- Monto del capital

- Intereses generados

- Fecha de vencimiento


## Fase 2: Diseño


## Bibliografía