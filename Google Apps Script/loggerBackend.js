//Funktions to load and save the target sheet
function setId(id){
  PropertiesService.getScriptProperties().setProperty('tableID', id);
}
function gettId(){
  return PropertiesService.getScriptProperties().getProperty('tableID');
}

//*** Recive and save JSON data */
function writeArraytoSheet(data){
   //Open Spreadsheet
    var sheet = SpreadsheetApp.openByUrl(gettId()).getSheets()[0];
    //last written row
    var lastRow = sheet.getLastRow();
    //write
    sheet.getRange(lastRow + 1,1,data.length, data[0].length).setValues(data);
}

//Json parser
function ParseJSON(jsonData){
   var data = [];
   var tmpData;
  var datasets = jsonData["data"]["numOfSets"];
  var DHTSensors = jsonData["data"]["numOfDHT"];
  for (let set = 0; set < datasets; set++)  {
    var dataSet = [];
      //set value time
      let tmpTime;
      tmpTime =new Date()
      tmpTime.setSeconds(tmpTime.getSeconds() );
      dataSet.push(tmpTime);

      //Set Data
      let jsonDataSet = jsonData["data"]["datasets"][set]
      let id = jsonDataSet["id"];
      let timeSpan = jsonDataSet["timeSpan"];
      dataSet.push(id, timeSpan);

      //Door
      let doorData = jsonDataSet["Door"];
      let angle = doorData["openAngle"];
      let openState = doorData["openState"];
      let openTime = doorData["openTime"];
      dataSet.push(angle, openState, openTime);

      // Power 
      let powerData = jsonDataSet["Power"];
      let powerState = powerData["powerState"];
      let powerAvg = powerData["powerAvg"];
      let timeInState = powerData["timeInState"];
      dataSet.push( powerState, powerAvg, timeInState);  

      //DHT values  
      for (let dht = 0; dht < DHTSensors; dht++) {
        // Werte einlesen
        let dhtSensor = jsonDataSet["DHTSensors"][dht];
        let temperatur = dhtSensor["Tmp"];
        let humidity = dhtSensor["Humid"];
        dataSet.push(temperatur, humidity);  
      }
      //push clomplete set
    data.push(dataSet);
  }
  //write all Sets
  writeArraytoSheet(data);
}

//http Post
function doPost(request) {
   //http Post Data
    var jsonString = request.postData.getDataAsString();
    var jsonData = JSON.parse(jsonString);
    ParseJSON(jsonData);
    
}

//*** New Sheet functions */
//Daily triggerd
function addTable(){ 
  //datum
  var datum = Utilities.formatDate(new Date(), "GMT+1", "dd/MM/yyyy - HH:mm");
  var ssNew = SpreadsheetApp.create('Logger test ' + datum);
  //save ID
  setId(ssNew.getUrl());
  SpreadsheetApp.setActiveSpreadsheet(ssNew);
  //add sheet
  addSheet();
}

function addSheet(){
  //Add Sheet in Table and delete stock one
  var datum = Utilities.formatDate(new Date(), "GMT+1", "dd/MM/yyyy - HH:mm");
  // Add a new sheet and use A1 cell as the parameter cell.
  var newSheet = SpreadsheetApp.openByUrl(gettId()).insertSheet('Logger'+datum, 0);
  var tmpSheet = SpreadsheetApp.getActiveSpreadsheet().getSheets()[1];
  //create sheet with name, write heading
  SpreadsheetApp.setActiveSheet(tmpSheet);
  SpreadsheetApp.getActiveSpreadsheet().deleteActiveSheet();
  SpreadsheetApp.setActiveSheet(newSheet);
  writeHeading();
}

function writeHeading() {
 var data = ['Empfangszeitpukt','Datensatz ID','Aufnahme- zeitraum [ms]','Tür Winkel [grad]','Tür Offen','Tür in Status [ms]','Leistungs Status','Leistung [W]','Leistung in Status [ms]','Temp. 1 [°C]','Feucht. 1 [%]','Temp. 2 [°C]','Feucht. 2 [%]','Temp. 3 [°C]','Feucht. 3 [%]','Temp. 4 [°C]','Feucht. 4 [%]','Temp. 5 [°C]','Feucht. 5 [%]'];
 SpreadsheetApp.openByUrl(gettId()).getSheets()[0].getRange(1,1,1, data.length).setValues([data]);
}