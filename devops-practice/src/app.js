const express = require('express');
const app = express();
app.get('/', (req, res) => {
    res.send('Hello, World!');
});

app.get('/9', (req, res) => {
    res.status(404);    
    res.send('Hello, World!');
});

const port = process.env.PORT || 3000;

const server=app.listen(port, () => {
    console.log(`Server running on port ${ port }`);
});

module.exports = { app, server };