#ifndef JSON_h
#define JSON_h
#include "Menu.h"
#include "ArduinoJson.h"

class json_factory {
    public: 
    String final_json = ";";

    public: 
    String make_json(void);
};

String json_factory :: make_json(void) {
    DynamicJsonDocument doc(2048); // Ajusta el tamaño si es necesario

    doc["ID_Casilla"] = 123;

    myrtc.get_time();
    myrtc.format_date('/');
    myrtc.format_time();
    
    // Crear un array JSON para los votos y otros datos
    JsonArray votosArray = doc.createNestedArray("Datos");

    // Iterar a través de los votos y añadirlos al array JSON
    for (int i = 0; i < myMenu.numVotos; i++) {
        JsonObject votoObj = votosArray.createNestedObject();
        votoObj["Partido"] = myMenu.votos[i].nombrePartido;
        votoObj["Candidatura"] = myMenu.votos[i].tipoCandidatura;
        votoObj["Candidato"] = myMenu.votos[i].nombreCandidato;
    }

    // Agregar objeto de fecha y hora
    JsonObject fechaHoraObj = votosArray.createNestedObject();
    fechaHoraObj["Fecha"] = myrtc.fecha;
    fechaHoraObj["Hora"] = myrtc.tiempo;

    // Agregar objeto de latitud y longitud
    JsonObject latLongObj = votosArray.createNestedObject();
    latLongObj["Latitud"] = 197.23;
    latLongObj["Longitud"] = 812121;

    String output;
    serializeJsonPretty(doc, output);
    return output;
}
#endif
