---
title: Project web con Vue
---
# Proyecto web con Vue

## Pasos previos
Primero se prepara el entorno, se usa la versión última de nodejs. Si no es la última se 
descarga la última versión de la siguiente forma.
```bash
sudo apt remove nodejs -y
curl -fsSL https://deb.nodesource.com/setup_22.x | sudo -E bash -
sudo apt install -y nodejs
```
## Creación del proyecto
```bash
npm create vue@latest
npm install
npm run dev
```
Accesso a la URL del proyecto
```bash
http://localhost:5173
```

## Código
## Creación del componente Login
La plantilla HTML creada se aloja en un componente Login, ese componente se crea en la ruta /src/comnponents/Login.vue
```js
<template>
  <div class="container">
    <header>
      <h1>nBESS</h1>
    </header>

    <section class="login-section">
      <form class="login-form" @submit.prevent="login">
        <input v-model="user" type="text" placeholder="Usuario" />
        <input v-model="pass" type="password" placeholder="Contraseña" />
        <button type="submit">Entrar</button>
      </form>
    </section>

    <footer>
      <div>Izquierda</div>
      <div>Centro</div>
      <div>Derecha</div>
    </footer>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const user = ref('')
const pass = ref('')

const login = () => {
  console.log('Usuario:', user.value)
  console.log('Password:', pass.value)
}
</script>

<style scoped>
.container {
  display: grid;
  grid-template-rows: 35rem auto auto;
  min-height: 100vh;
  font-family: sans-serif;
}

header {
  background: linear-gradient(rgba(0,0,0,0.5), rgba(0,0,0,0.5)),
              url('https://picsum.photos/1200/800') center/cover;
  display: flex;
  justify-content: center;
  align-items: center;
}

header h1 {
  color: white;
  font-size: 3rem;
}

.login-section {
  display: flex;
  justify-content: center;
  align-items: center;
}

.login-form {
  display: flex;
  flex-direction: column;
  gap: 1rem;
  width: 250px;
}

input {
  border: none;
  border-bottom: 2px solid black;
  padding: 8px;
  outline: none;
}

button {
  padding: 10px;
  border-radius: 20px;
  border: none;
  background: black;
  color: white;
  cursor: pointer;
}

footer {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  text-align: center;
  padding: 20px;
}
</style>

```





## Acondicionamiento de App.vue
```js
<template>
  <Login />
</template>

<script setup>
import Login from './components/Login.vue'
</script>
```
