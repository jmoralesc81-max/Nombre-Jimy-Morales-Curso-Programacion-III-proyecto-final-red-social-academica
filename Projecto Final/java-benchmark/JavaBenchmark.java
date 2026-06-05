package com.mycompany.java.benchmark;

import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.TreeMap;

public class JavaBenchmark {

    static final int RECORDS = 10000;

    public static void main(String[] args) {

        System.out.println("\n=== BENCHMARK JAVA (" + RECORDS + " registros) ===");

        HashMap<Integer, String> hashMap = new HashMap<>();
        TreeMap<Integer, String> treeMap = new TreeMap<>();

        long start, end;
        double hashInsert, hashSearch, treeInsert, treeTraversal;

        start = System.nanoTime();
        for(int i = 1; i <= RECORDS; i++) {
            hashMap.put(i, "Estudiante " + i);
        }
        end = System.nanoTime();
        hashInsert = (end - start) / 1_000_000.0;

        start = System.nanoTime();
        for(int i = 1; i <= RECORDS; i++) {
            hashMap.get(i);
        }
        end = System.nanoTime();
        hashSearch = (end - start) / 1_000_000.0;

        System.out.println("HashMap Insert:    " + hashInsert + " ms");
        System.out.println("HashMap Search:    " + hashSearch + " ms");

        start = System.nanoTime();
        for(int i = 1; i <= RECORDS; i++) {
            treeMap.put(i, "Estudiante " + i);
        }
        end = System.nanoTime();
        treeInsert = (end - start) / 1_000_000.0;

        start = System.nanoTime();
        for(String value : treeMap.values()) {
            String temp = value;
        }
        end = System.nanoTime();
        treeTraversal = (end - start) / 1_000_000.0;

        System.out.println("TreeMap Insert:    " + treeInsert + " ms");
        System.out.println("TreeMap Traversal: " + treeTraversal + " ms");

        try {
            FileWriter file = new FileWriter("java_results.csv");
            file.write("language,operation,structure,records,time_ms\n");
            file.write("Java,insert,HashMap,"  + RECORDS + "," + hashInsert    + "\n");
            file.write("Java,search,HashMap,"  + RECORDS + "," + hashSearch    + "\n");
            file.write("Java,insert,TreeMap,"  + RECORDS + "," + treeInsert    + "\n");
            file.write("Java,traversal,TreeMap," + RECORDS + "," + treeTraversal + "\n");
            file.close();
            System.out.println("\njava_results.csv generado correctamente.");
        } catch(IOException e) {
            System.out.println("Error al generar CSV: " + e.getMessage());
        }
    }
}