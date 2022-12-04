const { createApp } = Vue

const app = createApp({
})

app.component('box-outer', {
    props: ['x', 'y'],
    template: `<div class="box-outer">
    <div v-bind:id=\`box\${x}-\${y}\` class="box">
      <div v-bind:id=\`box\${x}-\${y}-g\` class="box-inner"></div>
      <div v-bind:id=\`box\${x}-\${y}-h\` class="box-inner"></div>
      <div v-bind:id=\`box\${x}-\${y}-f\` class="box-inner"></div>
      <div v-bind:id=\`box\${x}-\${y}-prev\` class="box-inner"></div>
    </div>
  </div>`,
    data: function () {
        return {};
    }
})

app.mount('#app')

arrow = (dx, dy) => {
    if (dx == 0 && dy == 1)
        return '⬆'
    if (dx == 0 && dy == -1)
        return '⬇'
    if (dx == 1 && dy == 0)
        return '⬅'
    if (dx == -1 && dy == 0)
        return '➡'
    if (dx == 1 && dy == 1)
        return '↖'
    if (dx == 1 && dy == -1)
        return '↙'
    if (dx == -1 && dy == 1)
        return '↗'
    if (dx == -1 && dy == -1)
        return '↘'
    return '⬤'
}

const ROWS = 5
const COLUMNS = 7

boxUpdate = (x, y, x2, y2) => {
    console.log(x, y, x2, y2)
    if (x < 1 || y < 1 || x > COLUMNS || y > ROWS)
        return;
    if (blocked[x-1][y-1])
        return;

    const newG = g[x2 - 1][y2 - 1] + Math.floor(10 * Math.sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2)))
    if (newG >= g[x - 1][y - 1])
        return;

    g[x - 1][y - 1] = newG;

    document.getElementById(`box${x}-${y}-g`).innerHTML = `g: ${g[x - 1][y - 1]}`
    document.getElementById(`box${x}-${y}-h`).innerHTML = `h: ${h(x, y)}`
    document.getElementById(`box${x}-${y}-f`).innerHTML = `f: ${g[x - 1][y - 1] + h(x, y)}`
    document.getElementById(`box${x}-${y}-prev`).innerHTML = `${arrow(x - x2, y - y2)}`

    document.getElementById(`box${x}-${y}`).onclick = boxClick(x, y)
    document.getElementById(`box${x}-${y}`).classList.add('box-clickable')
}

boxClick = (x, y) => {
    return () => {
        for (let _x = -1; _x <= 1; _x++) {
            for (let _y = -1; _y <= 1; _y++) {
                if (_x == 0 && _y == 0)
                    continue;
                boxUpdate(x + _x, y + _y, x, y)
            }
        }

        document.getElementById(`box${x}-${y}`).onclick = null
        document.getElementById(`box${x}-${y}`).classList.remove('box-clickable')
        document.getElementById(`box${x}-${y}`).classList.add('box-clicked')
    }
}

h = (x, y) => {
    let t = x - 1 < y - 1 ? x - 1 : y - 1
    t = t < 0 ? -t : t
    let t2 = x - 1 + y - 1 - 2 * t
    t2 = t2 < 0 ? -t2 : t2
    return 10 * t2 + 14 * t
}

g = []
blocked = []

for (let x = 1; x <= COLUMNS; x++) {
    g.push([])
    blocked.push([])
    for (let y = 1; y <= ROWS; y++) {
        g[g.length - 1].push(Infinity)
        blocked[blocked.length - 1].push(false)
    }
}

blocked[1][2] = true
blocked[2][2] = true
blocked[2][1] = true
blocked[3][1] = true
blocked[3][0] = true

document.getElementById('box2-3').classList.add('box-blocked')
document.getElementById('box3-3').classList.add('box-blocked')
document.getElementById('box3-2').classList.add('box-blocked')
document.getElementById('box4-2').classList.add('box-blocked')
document.getElementById('box4-1').classList.add('box-blocked')

document.getElementById(`box6-4`).classList.add("box-start")
document.getElementById(`box6-4`).onclick = boxClick(6, 4)
document.getElementById(`box6-4`).classList.add('box-clickable')
g[5][3] = 0
document.getElementById(`box6-4-g`).innerHTML = `g: ${g[5][3]}`
document.getElementById(`box6-4-h`).innerHTML = `h: ${h(6, 4)}`
document.getElementById(`box6-4-f`).innerHTML = `f: ${g[5][3] + h(6, 4)}`

document.getElementById(`box1-1`).classList.add("box-target")

