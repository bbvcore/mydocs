  
:::tip[Información de la librería]
- Web oficial: https://www.langchain.com/langgraph
:::

### Instalación
Usar la API, para ello hace falta un token de OpenAI y se añade al .env. 

En el package.json hay que añadir el soporte a módulos.
```javascript
"type": "module"
```

Crear un fichero llamado agent.js
```javascript
import OpenAI from "openai";
import dotenv from "dotenv";

dotenv.config();

const openai = new OpenAI({
  apiKey: process.env.OPENAI_API_KEY,
});

let conversation = [
  {
    role: "system",
    content: "Asistente experto en informática."
  }
];

async function chat(userInput) {
  conversation.push({
    role: "user",
    content: userInput
  });

  const response = await openai.chat.completions.create({
    model: "gpt-4o-mini",
    messages: conversation,
  });

  const assistantMessage = response.choices[0].message;

  conversation.push(assistantMessage);

  return assistantMessage.content;
}

// Test
(async () => {
  const reply = await chat("Qué es CSS?");
  console.log(reply);
})();

```
### Conseguir una Key
```bash
https://platform.openai.com/api-keys
```