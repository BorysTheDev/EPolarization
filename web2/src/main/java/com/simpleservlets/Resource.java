package com.simpleservlets;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;

@Path("/hello2")
public class Resource {

    @POST
    @Consumes({MediaType.APPLICATION_XML, MediaType.APPLICATION_JSON})
    @Produces({MediaType.TEXT_PLAIN})
    public String getParabolaParam(ParabolaParam receivedParabolaParam) {
       // System.out.println(receivedParabolaParam);

        return receivedParabolaParam.toString();
    }


  /*  @POST
    @Consumes({MediaType.APPLICATION_FORM_URLENCODED})
    @Produces({MediaType.TEXT_PLAIN})
    public String getParabolaParam(String string) {
        System.out.println(string);
        return string;
    }
         */

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String getParabolaParam2() {
        ParabolaParam parabolaParam = new ParabolaParam(-1,1,1);
        System.out.println(parabolaParam);
        return parabolaParam.toString();
    }
}
