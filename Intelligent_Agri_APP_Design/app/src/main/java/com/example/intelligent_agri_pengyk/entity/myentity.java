package com.example.intelligent_agri_pengyk.entity;

import android.app.Application;


public class myentity extends Application{

    private Integer
            shui=0,fengshan=0,guang=0,baojing=1,
            co2concentration=26,co2min=20,co2max=40,
            beam=67,beammin=60,beammax=80,
            soiltemperature=12,soiltemperaturemax=90,soiltemperaturemin=0,
            soilmoisture=1,soilmoisturemax=40,soilmoisturemin=20,
            airtemperature=26,airtemperaturemax=40,airtemperaturemin=20,
            airmoisture=70,airmoisturemax=80,airmoisturemin=60;
    private String ip;

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }
    public Integer getShui() {
        return shui;
    }

    public void setShui(Integer shui) {
        this.shui = shui;
    }

    public Integer getFengshan() {
        return fengshan;
    }

    public void setFengshan(Integer fengshan) {
        this.fengshan = fengshan;
    }

    public Integer getGuang() {
        return guang;
    }

    public void setGuang(Integer guang) {
        this.guang = guang;
    }

    public Integer getBaojing() {
        return baojing;
    }

    public void setBaojing(Integer baojing) {
        this.baojing = baojing;
    }

    public Integer getCo2concentration() {
        return co2concentration;
    }

    public void setCo2concentration(Integer co2concentration) {
        this.co2concentration = co2concentration;
    }

    public Integer getCo2min() {
        return co2min;
    }

    public void setCo2min(Integer co2min) {
        this.co2min = co2min;
    }

    public Integer getCo2max() {
        return co2max;
    }

    public void setCo2max(Integer co2max) {
        this.co2max = co2max;
    }

    public Integer getBeam() {
        return beam;
    }

    public void setBeam(Integer beam) {
        this.beam = beam;
    }

    public Integer getBeammin() {
        return beammin;
    }

    public void setBeammin(Integer beammin) {
        this.beammin = beammin;
    }

    public Integer getBeammax() {
        return beammax;
    }

    public void setBeammax(Integer beammax) {
        this.beammax = beammax;
    }

    public Integer getSoiltemperature() {
        return soiltemperature;
    }

    public void setSoiltemperature(Integer soiltemperature) {
        this.soiltemperature = soiltemperature;
    }

    public Integer getSoiltemperaturemax() {
        return soiltemperaturemax;
    }

    public void setSoiltemperaturemax(Integer soiltemperaturemax) {
        this.soiltemperaturemax = soiltemperaturemax;
    }

    public Integer getSoiltemperaturemin() {
        return soiltemperaturemin;
    }

    public void setSoiltemperaturemin(Integer soiltemperaturemin) {
        this.soiltemperaturemin = soiltemperaturemin;
    }

    public Integer getSoilmoisture() {
        return soilmoisture;
    }

    public void setSoilmoisture(Integer soilmoisture) {
        this.soilmoisture = soilmoisture;
    }

    public Integer getSoilmoisturemax() {
        return soilmoisturemax;
    }

    public void setSoilmoisturemax(Integer soilmoisturemax) {
        this.soilmoisturemax = soilmoisturemax;
    }

    public Integer getSoilmoisturemin() {
        return soilmoisturemin;
    }

    public void setSoilmoisturemin(Integer soilmoisturemin) {
        this.soilmoisturemin = soilmoisturemin;
    }

    public Integer getAirtemperature() {
        return airtemperature;
    }

    public void setAirtemperature(Integer airtemperature) {
        this.airtemperature = airtemperature;
    }

    public Integer getAirtemperaturemax() {
        return airtemperaturemax;
    }

    public void setAirtemperaturemax(Integer airtemperaturemax) {
        this.airtemperaturemax = airtemperaturemax;
    }

    public Integer getAirtemperaturemin() {
        return airtemperaturemin;
    }

    public void setAirtemperaturemin(Integer airtemperaturemin) {
        this.airtemperaturemin = airtemperaturemin;
    }

    public Integer getAirmoisture() {
        return airmoisture;
    }

    public void setAirmoisture(Integer airmoisture) {
        this.airmoisture = airmoisture;
    }

    public Integer getAirmoisturemax() {
        return airmoisturemax;
    }

    public void setAirmoisturemax(Integer airmoisturemax) {
        this.airmoisturemax = airmoisturemax;
    }

    public Integer getAirmoisturemin() {
        return airmoisturemin;
    }

    public void setAirmoisturemin(Integer airmoisturemin) {
        this.airmoisturemin = airmoisturemin;
    }

    @Override
    public String toString() {
        return "message{" +
                "co2concentration=" + co2concentration +
                ", co2min=" + co2min +
                ", co2max=" + co2max +
                ", beam=" + beam +
                ", beammin=" + beammin +
                ", beammax=" + beammax +
                ", soiltemperature=" + soiltemperature +
                ", soiltemperaturemax=" + soiltemperaturemax +
                ", soiltemperaturemin=" + soiltemperaturemin +
                ", soilmoisture=" + soilmoisture +
                ", soilmoisturemax=" + soilmoisturemax +
                ", soilmoisturemin=" + soilmoisturemin +
                ", airtemperature=" + airtemperature +
                ", airtemperaturemax=" + airtemperaturemax +
                ", airtemperaturemin=" + airtemperaturemin +
                ", airmoisture=" + airmoisture +
                ", airmoisturemax=" + airmoisturemax +
                ", airmoisturemin=" + airmoisturemin +
                '}';
    }
}
