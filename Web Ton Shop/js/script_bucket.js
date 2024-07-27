const productList = JSON.parse(localStorage.getItem('productList')) || [];

function getPrice(item) {
    switch (item) {
        case 1: return 1000000.0;
        case 2: return 65000.0;
        case 3: return 50000.0;
        case 4: return 500000.0;
        case 5: return 100000.0;
        default: return 0.0;
    }
}

function getItemName(item) {
    switch (item) {
        case 1: return "Shoes";
        case 2: return "Shirt";
        case 3: return "Pants";
        case 4: return "Ball";
        case 5: return "Set of Pants and Shirt";
        default: return "";
    }
}

function getSportName(sport) {
    switch (sport) {
        case 1: return "Volleyball";
        case 2: return "Basketball";
        case 3: return "Badminton";
        default: return "";
    }
}

function addProduct() {
    const sport = parseInt(document.getElementById('sport').value);
    const item = parseInt(document.getElementById('item').value);
    const quantity = parseInt(document.getElementById('quantity').value);
    const price = getPrice(item);

    const product = {
        sport: sport,
        item: item,
        price: price,
        quantity: quantity,
    };

    productList.push(product);
    localStorage.setItem('productList', JSON.stringify(productList));
    alert("DONE");
    displayList();

    // Show the "Complete" message
    showCompleteMessage();
}

function deleteProduct(index) {
    if (index !== undefined) {
        productList.splice(index, 1);
    } else {
        productList.length = 0; // Clear the entire list
    }
    localStorage.setItem('productList', JSON.stringify(productList));
    displayList();
}

function displayList() {
    const tableBody = document.querySelector('#productTable tbody');
    tableBody.innerHTML = '';

    productList.forEach((product, index) => {
        const row = document.createElement('tr');

        row.innerHTML = `
            <td>${getSportName(product.sport)}</td>
            <td>${getItemName(product.item)}</td>
            <td>${product.price.toFixed(2)}</td>
            <td>${product.quantity}</td>
            <td>${(product.price * product.quantity).toFixed(2)}</td>
            <td><button onclick="deleteProduct(${index})">Delete</button></td>
        `;

        tableBody.appendChild(row);

        // Highlight the newly added row
        if (index === productList.length - 1) {
            row.classList.add('highlight');
            setTimeout(() => {
                row.classList.remove('highlight');
            }, 2000);
        }
    });

    // Calculate the total price
    let total = 0;

    productList.forEach(product => {
        total += product.price * product.quantity;
    });

    // Update total price in the DOM
    document.getElementById('totalPrice').innerText = `Total Price: ${total.toFixed(2)}`;

    // Show or hide the order summary section
    const orderSummary = document.getElementById('orderSummary');
    if (productList.length > 0) {
        orderSummary.style.display = 'block';
    } else {
        orderSummary.style.display = 'none';
    }
}

function confirmOrder() {
    let total = 0;

    productList.forEach(product => {
        total += product.price * product.quantity;
    });

    document.getElementById('totalPrice').innerText = `Total Complete Price: ${total.toFixed(2)}`;

    alert("Payment Complete");

    // Delay the deletion by 1 seconds
    setTimeout(() => {
        deleteProduct(); // Clear the entire list after confirming the order
    }, 1000);
}

// Function to show the "Complete" message
function showCompleteMessage() {
    const messageDiv = document.createElement('div');
    messageDiv.classList.add('complete-message');
    messageDiv.innerText = 'Complete';

    document.body.appendChild(messageDiv);

    // Remove the message after 2 seconds
    setTimeout(() => {
        document.body.removeChild(messageDiv);
    }, 2000);
}

// Display the list when the page loads
document.addEventListener('DOMContentLoaded', displayList);
