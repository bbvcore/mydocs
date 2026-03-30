---
title: Angular
---
# Angular
Angular es un framework muy completo y complejo basado en Javascript y que hace uso de TypeScript.
## Flujo 
Angular posee la estructura más compleja de los frameworks y librerías de JS destinadas a la creación de aplicaciones web.
### Histórico: Versión anterior a la 14
Se organizaba en torno a los módulos (NgModule) y la estructura de los principales ficheros era la siguiente.
<details>
<summary>
Ficheros principales del flujo de Angular 
</summary>


- index.html: contiene la entrada al DOM del componente raíz con el siguiente tag.
```bash
<app-root></app-root>
```
- **main.ts**: inicializa la aplicación cargando el módulo principal **AppModule**.
- **app.module.ts**: es el módulo raíz que contiene los componentes, las directivas y los servicios que estarán disponibles globalmente.
- **app.component.ts**: el encargado de renderizar el componente raíz 
```bash
<app-root>
```
El flujo entonces se organiza de la siguiente forma:
```bash
main.ts -> AppModule -> AppComponent
```
</details>

Se solita trabajar con módulos que gestionaban componentes y el módulo que lo gestionaba todo era AppModule.
```bash
bootstrapModule(AppModule)
```
Donce el centro de configuración era el fichero **app.module.ts**.

#### Componentes, pipes o directivas
Estos elementos se añadían en **declarations** dentro del módulo y los módulos que querían usar estos elementos debían de usar **import** para añadir dicho módulo, y si se quería usar directivas o componentes en otros módulos habían que exportalos de forma directa con **exports**.

#### Servicios (providers)
También funcionaban a nivel de módulo. Se podían usar globalmente:
```bash
providedIn:'root'
```
O desde otro módulo mediante:
```bash
providedIn:<nameModulo>
```
Con lo cual la configuración de un servicio para un módulo requería la importación y así era fácil tener instancias duplicadas.

### Versión posterior a la 14 (Flujo moderno)
Con la versión 14 se adopta una estructura base diferente.

<details>
<summary>
Ver la nueva estructura
</summary>

- **index.html**: contine la entrada al DOM.
- **main.ts**: se encarga de cargar el módulo app cargando directamente los componentes raíz.
- **app.ts**: componente raíz standalone
- **app.html**: template del componente raíz

</details>

Ahora **main.ts** y los **componentes** no necesitan usar un módulo, los módulos son opcionales, ahora Angular se orienta más a componentes. En este nuevo flujo AppComponent es quién coordina, quedando el flujo así:
```bash
main.ts -> AppComponent (standalone)
```
#### App.config.ts
Es el centro de configuración, de esta forma se evita el problema de exportar e importar entre módulos, la configuración se centraliza en este fichero. Los módulos con este nuevo enfoque pasan a ser opcionales la mayoría de casos. Los componentes, pipelines o directivas son standalone y se pueden importar de forma directa desapareciendo los imports/exports ente módulos.


## Requisitos previos
Es necesario tener instalado NodeJS.

## Instalación
### Instalación de la terminal de angular
```bash
npm install -g @angular/cli
```
### Crear un proyecto
El comando base propio de angular para llevar a cabo cualquier acción es **ng**. En este caso, como funciona angular en versiones modernas, se creará el proyecto en modo standalone. 
```bash
ng new <nameProject> --standalone
```
## Binding
Dentro del binding o enlace de datos en angular se dan 4 tipos
### Interpolación
```javascript
{{ variable }}
```
### Property Binding
```javascript
<img [src]="variable"><!-- Property binding -->
```
### Event Binding
```javascript
<button (click)="function()">click</button>
<p>Variable: {{ variable }}</p>
```
### Two Way manual
```javascript
<input [value]="variable" (input)="onInput($event)">
```
### Two Way data binding - banana box
```javascript
[(ngModel)]="variable"
<input [(ngModel)]="title">
```

## Caso de uso: Uso del Binding
El fichero main.ts se deja como está, es en app.config.ts donde se han de realizar operaciones.

:::tip
- Providers: proveedores, son inyectores de dependencias.
Los más usados son:   provideRouter(routes), provideHttpClient(), importProvidersFrom(FormsModule)
```javascript
import { ApplicationConfig, importProvidersFrom } from '@angular/core';
import { provideRouter } from '@angular/router';
import { provideHttpClient } from '@angular/common/http';
import { FormsModule } from '@angular/forms';
import { routes } from './app.routes';
```
:::

### Fichero app.ts
### Fichero app.html
### Fichero app.css


## Caso de uso de consumo de API externa (servicios)
Requiere un provider global: HttpClient en el fichero de configuración  app.config.ts
```javascript
import { provideHttpClient } from '@angular/common/http';
import { FormsModule } from '@angular/forms'; // para disponer de ngModel, por si acaso
export const appConfig: ApplicationConfig = {
  providers: [
    provideHttpClient(),
    importProvidersFrom(FormsModule)
  ]
};
```

## Caso de uso: Consumo API
### Comandos
#### Creación componentes y servicios
Desde el directorio de la aplicación
```bash
ng generate component components/dragon-list --standalone --skip-tests --flat=false
ng generate component components/users-list --standalone --skip-tests --flat=false
ng generate service services/dragon-ball --skip-tests
ng generate service services/db --skip-tests
```

#### Backend nodejs
```bash
mkdir backend
cd backend
npm init -y
npm install express mysql2 cors dotenv
```
##### Server.js
```javascript
// backend/server.js
import express from 'express';
import cors from 'cors';
import mysql from 'mysql2/promise';
import dotenv from 'dotenv';

dotenv.config();

const app = express();
app.use(cors());
app.use(express.json());

const pool = mysql.createPool({
  host: process.env.DB_HOST || 'localhost',
  user: process.env.DB_USER || 'root',
  password: process.env.DB_PASS || '',
  database: process.env.DB_NAME || 'angular_demo',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
});

app.get('/api/users', async (req, res) => {
  try {
    const [rows] = await pool.query('SELECT id, name, email FROM users ORDER BY id ASC');
    res.json(rows);
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: 'db error' });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Backend listening on http://localhost:${PORT}`));
```

#### Fichero env
```bash
DB_HOST=localhost
DB_USER=root
DB_PASS=tu_password
DB_NAME=angular_demo
PORT=3000
```

#### Datos para base
```sql
-- backend/db/init.sql
CREATE DATABASE IF NOT EXISTS angular_api CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE angular_demo;

CREATE TABLE IF NOT EXISTS users (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  email VARCHAR(150)
);

INSERT INTO users (name, email) VALUES
('Bulma Briefs', 'bulma@example.com'),
('Son Goku', 'goku@example.com'),
('Vegeta', 'vegeta@example.com');
```
### Configurar el componente raíz
En app.ts se ha de añadir lo siguiente
```javascript
import { DragonBallComponent } from './components/dragon-ball';
import { UsersComponente } from './components/users';
```
En el decorador del componente se han de importar añadiendolos en imports
```javascript
imports:[DragonBallComponent, UsersComponent]
```
Y en el export de la clase se puede generar alguna propiedad, por ejemplo un titulo para interpolar
```javascript
title="Aplicación Angular para el consumo del API de Dragon Ball";
```
### Configurar el html
Se puede configurar directamente en el componente en la propiedad templateUrl del decorador, pero 
en este caso se usará una referencia a fichero html app.html.
```html
<main>
<h2>{{ title }}</h2>
<section>
<app-dragon-ball></app-dragon-ball> <!-- Componente dragón ball -->
</section>
<section>
<app-users></app-users> <!-- Componente de users -->
</main>
```
### Creación de servicios
se procede a la creación de un directorio services en /src y de los ficheros correspondientes, los ficheros de servicios han de llevar la extensión ".service.ts".

#### Servicio API dragon ball
dragon-ball.service.ts
```javascript
// src/app/services/dragon-ball.service.ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

export interface DragonCharacter {
  id?: number;
  name: string;
  // añadir otros campos según la API
}

@Injectable({ providedIn: 'root' })
export class DragonBallService {
  // Cambiar por la API pública que se quiera usar
  private apiUrl = 'https://dragon-ball-api.herokuapp.com/api/characters';

  constructor(private http: HttpClient) {}

  getCharacters(): Observable<DragonCharacter[]> {
    return this.http.get<DragonCharacter[]>(this.apiUrl);
  }
}
```
#### Servicio conexión DB
Se crea el fichero **database.service.ts**
```javascript
// src/app/services/db.service.ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

export interface User {
  id: number;
  name: string;
  email?: string;
}

@Injectable({ providedIn: 'root' })
export class DbService {
  private apiUrl = 'http://localhost:3000/api/users'; // backend
  constructor(private http: HttpClient) {}

  getUsers(): Observable<User[]> {
    return this.http.get<User[]>(this.apiUrl);
  }
}

```
### Componentes
#### Componente Dragon Ball
```javascript
// src/app/components/dragon-list.ts
import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { DragonBallService, DragonCharacter } from '../services/dragon-ball.service';

@Component({
  selector: 'app-dragon-list',
  standalone: true,
  imports: [CommonModule],
  template: `
    <div *ngIf="loading">Cargando personajes...</div>
    <div *ngIf="error" style="color:red">{{ error }}</div>
    <ul *ngIf="characters?.length">
      <li *ngFor="let c of characters">
        {{ c.name }}
      </li>
    </ul>
  `
})
export class DragonListComponent implements OnInit {
  characters: DragonCharacter[] = [];
  loading = false;
  error = '';

  constructor(private db: DragonBallService) {}

  ngOnInit(): void {
    this.loading = true;
    this.db.getCharacters().subscribe({
      next: (data) => {
        this.characters = data;
        this.loading = false;
      },
      error: (err) => {
        this.error = 'ERROR! No se pudo cargar la API';
        this.loading = false;
        console.error(err);
      }
    });
  }
}
```
#### Componente base de datos
```javascript
// src/app/components/users-list.ts
import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { DbService, User } from '../services/db.service';

@Component({
  selector: 'app-users-list',
  standalone: true,
  imports: [CommonModule],
  template: `
    <div *ngIf="loading">Cargando usuarios desde el backend...</div>
    <div *ngIf="error" style="color:red">{{ error }}</div>
    <ul *ngIf="users?.length">
      <li *ngFor="let u of users">
        {{ u.id }} — {{ u.name }} ({{ u.email || 'sin email' }})
      </li>
    </ul>
  `
})
export class UsersListComponent implements OnInit {
  users: User[] = [];
  loading = false;
  error = '';

  constructor(private db: DbService) {}

  ngOnInit(): void {
    this.loading = true;
    this.db.getUsers().subscribe({
      next: (data) => { this.users = data; this.loading = false; },
      error: (err) => { this.error = 'ERROR! No se pudo conectar al backend'; this.loading = false; console.error(err); }
    });
  }
}
```







