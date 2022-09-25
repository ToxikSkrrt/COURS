const express = require('express');
const { Client } = require('pg');
const app = express();
const port = 8080;

const client = new Client({
    database: 'dix', 
    port : 17680
});

client.connect()
    .then(() => {
        console.log('Connected to database');
    })
    .catch((e) => {
        console.log('Error connecting to database');
        console.log(e);
    });


app.listen(port, () => {
    console.log(`Le serveur écoute sur http://localhost:8080`)
})

app.get('/index.htlml', async (req, res) => {
    try {
        open(index.html)
    } catch (e) {
        res.send(e);
    }
});



app.post('/nouveau', async (req, res) => {
    try {
        let id_etudiant = req.body.id_etudiant
        let Nom = req.body.nom
        let Prenom = req.body.prenom
        let option1 = req.body.option1
        let option2 = req.body.option2
        let option3 = req.body.option3
        await client.query(`INSERT INTO inscription (id_etudiant, Nom, Prenom , option1, option2, option3) VALUES (${id_etudiant}, ${Nom}, ${Prenom}, ${option1}, ${option2}, ${option3};`)
        
        const sqlResult = await client.query(sqlQuery); 
        res.send(sqlResult.rows[0]); 
        res.render('inscription', { id_etudiant, nom, preneom, option1, option2, option3});
    } catch (e) {
        res.send(e);
    }
});