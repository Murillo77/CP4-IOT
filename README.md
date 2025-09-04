# Projeto ESP32 – Classificação de Sinais com Decision Tree e SVM

**Integrantes:**  
- Guilherme Paes Camargo | RM555166  
- Icaro Albuquerque | RM555131  
- Murillo Santanna | RM557183  
- Cicero Serafim | RM556996  
- Eduardo Miguel | RM555871  

**link do vídeo**
Link: https://youtu.be/fv9fNMF7fZs
---

## Descrição do Projeto
Este projeto utiliza um ESP32 para capturar sinais (simulados ou reais), extrair features (`mean`, `std`, `rms`, `ptp`) e classificar os sinais usando **modelos de Machine Learning** exportados em C (Decision Tree e SVM) gerados pelo PyCaret com M2C.  

O código foi desenvolvido para **funcionar no simulador Wokwi**, permitindo teste sem sensor físico.

---

## Estrutura do Projeto
- `dataset_features.csv` – CSV com dados de treinamento (features + labels).  
- `train_models.py` – Script Python que gera `model_dt.c` e `model_svm.c`.  
- `model_dt.c` / `model_svm.c` – Modelos exportados em C.  
- `esp32_main.ino` – Código do ESP32 que lê sinais, calcula features e prediz classe.  

---

## Pinos do ESP32
| Função               | Pino ESP32 |
|----------------------|------------|
| Entrada ADC          | 34         |
| LED Decision Tree = 1 | 2         |
| LED Decision Tree = 0 | 4         |

> Obs.: No código simulado, o ADC é substituído por sinais gerados por software.

---

## Como Rodar

### 1. Gerar CSV e modelos (Python)
1. Abra o Colab ou outro ambiente Python.  
2. Execute o script `train_models.py`:
```bash
python train_models.py
