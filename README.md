
# Projeto ESP32 – Classificação de Sinais com Decision Tree e SVM

**Integrantes:**  
- Guilherme Paes Camargo | RM555166  
- Icaro Albuquerque | RM555131  
- Murillo Santanna | RM557183  
- Cicero Serafim | RM556996  
- Eduardo Miguel | RM555871  

**Link do vídeo:**  
[https://youtu.be/fv9fNMF7fZs](https://youtu.be/fv9fNMF7fZs)

---

## Descrição do Projeto
Este projeto utiliza um ESP32 para capturar sinais (simulados ou reais), extrair features (`mean`, `std`, `rms`, `ptp`) e classificar os sinais usando **modelos de Machine Learning** exportados em C (Decision Tree e SVM) gerados pelo PyCaret com M2C.  

O código foi desenvolvido para **funcionar no simulador Wokwi**, permitindo teste sem sensor físico.

---

## Estrutura do Projeto
- `dataset_features.csv` – CSV com dados de treinamento (features + labels)  
- `train_models.py` – Script Python que gera `model_dt.c` e `model_svm.c`  
- `model_dt.c` / `model_svm.c` – Modelos exportados em C  
- `esp32_main.ino` – Código do ESP32 que lê sinais, calcula features e prediz classe  

---

## Pinos do ESP32
| Função               | Pino ESP32 |
|----------------------|------------|
| Entrada ADC          | 34         |
| LED Decision Tree = 1 | 2         |
| LED Decision Tree = 0 | 4         |

> Obs.: No código simulado, o ADC é substituído por sinais gerados por software.

---

## Pré-requisitos
- Arduino IDE 1.8+ ou VSCode com PlatformIO  
- Placa ESP32 instalada na IDE  
- Simulador opcional: [Wokwi](https://wokwi.com/)

---

## Como Rodar

### 1. Gerar CSV e modelos (Python)
1. Abra o Colab ou outro ambiente Python  
2. Execute o script `train_models.py`:

```bash
python train_models.py
````

Isso vai gerar os arquivos `model_dt.c` e `model_svm.c` a partir do `dataset_features.csv`.

---

### 2. Configurar o Arduino IDE / VSCode

* Abra o arquivo `esp32_main.ino`
* Verifique os pinos definidos para LED e ADC (veja tabela acima)
* Inclua os arquivos gerados no código:

```c
#include "model_dt.c"
#include "model_svm.c"
```

* Conecte o ESP32 ao computador

---

### 3. Upload e Teste

* Selecione a placa ESP32 correta na IDE
* Faça o upload do código para o ESP32
* Abra o Serial Monitor com **115200 baud** para ver as previsões em tempo real
* No **Wokwi**, basta iniciar a simulação para ver os LEDs e resultados da classificação

---

## Funções do Projeto

* Leitura de sinais: ADC ou sinal simulado
* Extração de features: `mean`, `std`, `rms`, `ptp`
* Classificação: Decision Tree e SVM
* Visualização: LEDs indicam a classe prevista

---

## Referências

* [PyCaret Documentation](https://pycaret.org/)
* [M2CGen](https://github.com/BayesWitnesses/m2cgen)
* [Wokwi ESP32 Simulator](https://wokwi.com/)

