# 🚀 GameServer-Main-Plugin-97x

![Version](https://img.shields.io/badge/GameServer-0.96.40T-blue)
![Client](https://img.shields.io/badge/Main-97.04-purple)
![Status](https://img.shields.io/badge/Status-Stable-success)
![Build](https://img.shields.io/badge/Build-OK-brightgreen)

## 📦 Informações

**GameServer versão:** 0.96.40T  
**Main:** Unpacked 97.04  

---

## 🧾 Resumo das Correções e Implementações

Este update traz uma evolução completa do sistema, focada em:

- 🔒 Estabilidade
- 🛡️ Segurança
- 🔄 Sincronização em tempo real
- 🎮 Melhor experiência do jogador

---

## ❤️ Correção no Sistema de Reset / Master Reset

- Corrigido bug crítico:
  - ❌ Mana zerando/travando após reset

- Nova ordem correta:
  - MaxLife → Life  
  - MaxMana → Mana  

- 🔄 Sincronização perfeita entre:
  - Client ⇄ Server

---

## 🖥️ Melhorias na Interface

- 📊 Título dinâmico na janela do jogo:
  - Ping
  - FPS
  - Resets
  - Cash
  - VIP

- ⚡ Atualização em tempo real

---

## ⚙️ F9 Stability Fix

### Corrigido:
- Crash ao minimizar  
- Falha ao restaurar  
- Conflito com hotkeys  

- 🔄 Novo sistema híbrido de teclado  

## ⌨️ Input Control (Hidden Mode)

- 🔒 Bloqueio total de teclas em segundo plano  

### Evita:
- Abrir inventário  
- Usar skills  
- Ações indevidas  

- ✅ Apenas **F9** permanece ativo 

## 🧩 Minimize System (F9 + Tray)

- 🟡 Minimizar para bandeja (tray)  
- 🎯 Ícone custom (`Main.ico`)  

### 🔄 Restaurar
- Tecla **F9**
- Clique no ícone da bandeja  

### 📋 Menu no Tray
- Abrir  
- Fechar  

---

## 🔢 Auto Reset / Auto Add Fix

- 🛑 Limite máximo por status: **32767**

### 🧠 Sistema inteligente:
- Bloqueia status que atingirem o limite  
- Continua distribuindo nos demais  

- 🔄 Para apenas quando **TODOS os status estão full**

### 💬 Mensagem exibida:
Você atingiu limite de pontos nos Status
- 🔒 Proteção total contra overflow  

---
