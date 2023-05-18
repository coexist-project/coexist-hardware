const options = document.querySelector(".options")
let connection = new WebSocket("ws://" + location.hostname + ":81", ['arduino'])

cconnection.url()
connection.onopen = () => {
    connection.send('Connect ' + new Date());
};
connection.addEventListener("message", (event) => {
    console.log(event.data);
})

const func = () => {
    const div = document.createElement('div')
    console.log('as')
    div.classList.add('option')
    div.textContent = 'new element'
    options.appendChild(div)
}