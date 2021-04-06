// define the callAPI function that takes a first name and last name as parameters
var callAPI = (firstName,lastName)=>{
    // instantiate a headers object
    var myHeaders = new Headers();
    // add content type header to object
    myHeaders.append("Content-Type", "application/json");
    // using built in JSON utility package turn object to string and store in a variable
    var raw = JSON.stringify(
        {
            "firstName":firstName,
            "lastName":lastName
        }
    );
    // create a JSON object with parameters for API call and store in a variable
    var requestOptions = {
        method: 'POST',
        headers: myHeaders,
        body: raw,
        redirect: 'follow'
    };
    // make API call with parameters and use promises to get response
    fetch("https://uovq2mpu95.execute-api.us-east-2.amazonaws.com/dev/test", requestOptions)
    .then(response => response.text())
    .then(result => alert(JSON.parse(result).body))
    .catch(error => console.log('error', error));
}

// $query = "SELECT wi.winery_name,
// w.year,
// w.wine_name,
// w.wine_id,
// w.description
// FROM wine w, winery wi, inventory i
// WHERE w.winery_id = wi.winery_id
// AND w.wine_id = i.wine_id
// AND w.description IS NOT NULL
// GROUP BY w.wine_id
// ORDER BY i.date_added DESC LIMIT 3";