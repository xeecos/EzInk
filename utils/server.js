const express = require('express')
const app = express()
const port = 3000
const urlencode = require('urlencode')
const { createCanvas } = require('canvas')
const canvas = createCanvas(200, 200)
const ctx = canvas.getContext('2d')

app.get('/', (req, res) => {
    let data = drawText(req.query.txt,req.query.size,req.query.font)
    let size = data.size;
    let buffer = Buffer.from([size,size].concat(data.bin));
    res.writeHead(200, {
        'Content-Type': 'bin',
        'Content-disposition': `attachment;filename=${urlencode(req.query.txt)}.bin`,
        'Content-Length': buffer.length
    });
    res.end(Buffer.from(buffer, 'binary'));
})


function drawText(c, size = 64, font = "SimSun") {
    ctx.fillStyle = "#ffffff";
    ctx.fillRect(0, 0, 200, 200);
    ctx.fillStyle = "#000000";
    ctx.font = `${size}px ${font}}`
    ctx.fillText(c, 10, size);
    // console.log(canvas.toDataURL())
    let pixels = ctx.getImageData(0, 0, size, size);
    let bin = [];
    let b = 0;
    let bIdx = 0;
    for (let i = 0; i < size; i++) {
        for (let j = 0; j < size; j++) {
            let idx = (i * size + j) * 4;
            let g = pixels.data[idx];
            b += (g < 128 ? 1 : 0) << bIdx;
            bIdx++;
            if (bIdx == 8) {
                bin.push(b);
                b = 0;
                bIdx = 0;
            }
        }
    }
    return { size, bin };
}

app.listen(port, () => {
    console.log(`EzInk app listening on port ${port}`)
})
