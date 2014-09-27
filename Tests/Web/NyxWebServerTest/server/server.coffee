express = require('express')
app = express()

#app.use(express.static('../client'))
app.use('/app/bower_components', (req, res, next) ->
    res.redirect("/bower_components#{req.url}")
)

app.use('/', express.static('../client'))

app.listen(8100)

