package com.simpleservlets;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement
public class ParabolaParam {
    private double ax;
    private double bx;
    private double b;

    public ParabolaParam() {
    }

    public ParabolaParam(double ax, double bx, double b) {
        this.ax = ax;
        this.bx = bx;
        this.b = b;
    }

    public double getAx() {
        return ax;
    }

    public void setAx(double ax) {
        this.ax = ax;
    }

    public double getBx() {
        return bx;
    }

    public void setBx(double bx) {
        this.bx = bx;
    }

    public double getB() {
        return b;
    }

    public void setB(double b) {
        this.b = b;
    }

    @Override
    public String toString() {
        return "Ax:" + ax + " Bx:" + bx + " b:" + b;
    }
}
