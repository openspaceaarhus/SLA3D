/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * MainFrame.java
 *
 * Created on Feb 13, 2011, 11:05:34 AM
 */
package dk.hackaarhus.fractal.sierpinski;

import java.io.File;
import javax.swing.JFileChooser;

/**
 *
 * @author ermh
 */
public class MainFrame extends javax.swing.JFrame {

    double baseLength;
    int recursionDepth;
    File outputFile;

    /** Creates new form MainFrame */
    public MainFrame() {
        initComponents();
        doReset(null);
    }

    public double getBaseLength() {
        return baseLength;
    }

    public void setBaseLength(double baseLength) {
        this.baseLength = baseLength;
        baseLengthField.setText(Double.toString(baseLength));
    }

    public File getOutputFile() {
        return outputFile;
    }

    public void setOutputFile(File outputFile) {
        this.outputFile = outputFile;
        this.outputFileField.setText(outputFile.toString());
    }

    public int getRecursionDepth() {
        return recursionDepth;
    }

    public void setRecursionDepth(int recursionDepth) {
        this.recursionDepth = recursionDepth;
        recursionDepthField.getModel().setValue(recursionDepth);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        baseLengthField = new javax.swing.JFormattedTextField();
        jLabel3 = new javax.swing.JLabel();
        recursionDepthField = new javax.swing.JSpinner();
        jLabel4 = new javax.swing.JLabel();
        outputFileField = new javax.swing.JTextField();
        jLabel5 = new javax.swing.JLabel();
        setButton = new javax.swing.JButton();
        generateButton = new javax.swing.JButton();
        cancelButton = new javax.swing.JButton();
        resetButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Sierpinski Fractal Parameters");

        jLabel1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        jLabel1.setText("Sierpinski Fractal Parameters");

        jLabel2.setText("Base Length:");

        baseLengthField.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.NumberFormatter()));
        baseLengthField.setHorizontalAlignment(javax.swing.JTextField.TRAILING);
        baseLengthField.setText("1");
        baseLengthField.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                onBaseLengthChange(evt);
            }
        });

        jLabel3.setText("Recursion Depth:");

        recursionDepthField.setModel(new javax.swing.SpinnerNumberModel(Integer.valueOf(3), Integer.valueOf(0), null, Integer.valueOf(1)));
        recursionDepthField.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                onRecursionDepthChanged(evt);
            }
        });

        jLabel4.setText("<html>File sizes are multiplied by 4 for each depth increase");

        outputFileField.setText("sierpinski.stl");
        outputFileField.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                onOutputFileChanged(evt);
            }
        });

        jLabel5.setText("Output File:");

        setButton.setText("Change");
        setButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                doSetOutputFilePressed(evt);
            }
        });

        generateButton.setText("Generate");
        generateButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                doGenerate(evt);
            }
        });

        cancelButton.setText("Cancel");
        cancelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                doCancel(evt);
            }
        });

        resetButton.setText("Reset");
        resetButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                doReset(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jLabel1, javax.swing.GroupLayout.DEFAULT_SIZE, 498, Short.MAX_VALUE)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel2)
                            .addComponent(jLabel3))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 237, Short.MAX_VALUE)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(recursionDepthField)
                            .addComponent(baseLengthField, javax.swing.GroupLayout.DEFAULT_SIZE, 153, Short.MAX_VALUE)))
                    .addComponent(jLabel4, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(jLabel5)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(outputFileField, javax.swing.GroupLayout.DEFAULT_SIZE, 330, Short.MAX_VALUE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(setButton, javax.swing.GroupLayout.PREFERRED_SIZE, 75, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(resetButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(cancelButton)
                        .addGap(18, 18, 18)
                        .addComponent(generateButton)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel2)
                    .addComponent(baseLengthField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jLabel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(recursionDepthField))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jLabel4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(outputFileField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel5)
                    .addComponent(setButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 58, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(generateButton)
                    .addComponent(cancelButton)
                    .addComponent(resetButton))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void doGenerate(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_doGenerate
        try {
            baseLengthField.commitEdit();
            Sierpinski.generateFractal(getRecursionDepth(), getBaseLength(), getOutputFile());
            System.exit(0);
        } catch (Exception ex) {
            throw new IllegalStateException(ex);
        }
    }//GEN-LAST:event_doGenerate

    private void doCancel(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_doCancel
        setVisible(false);
        System.exit(1);
    }//GEN-LAST:event_doCancel

    private void doReset(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_doReset
        setBaseLength(1);
        setRecursionDepth(3);
        setOutputFile(new File("sierpinski.stl"));
    }//GEN-LAST:event_doReset

    private void doSetOutputFilePressed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_doSetOutputFilePressed
        final File oldValue = getOutputFile().getAbsoluteFile();
        final File parentDir = oldValue.getParentFile();
        File dir = parentDir.getAbsoluteFile();
        JFileChooser fc = new JFileChooser(dir);
        fc.setFileFilter(new javax.swing.filechooser.FileFilter() {

            public boolean accept(File pathname) {
                return pathname.getName().toLowerCase().endsWith(".stl");
            }

            @Override
            public String getDescription() {
                return "STL File";
            }
        });
        fc.setCurrentDirectory(dir);
        fc.setSelectedFile(getOutputFile());
        
        int returnVal = fc.showDialog(this, "Change");
        
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            setOutputFile(fc.getSelectedFile());
        }
    }//GEN-LAST:event_doSetOutputFilePressed

    private void onBaseLengthChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_onBaseLengthChange
        double oldValue = getBaseLength();
        Number number = (Number) baseLengthField.getValue();
        if (number == null) {
            number = 0d;
        }
        double newValue = number.doubleValue();
        if (oldValue != newValue) {
            setBaseLength(newValue);
        }
    }//GEN-LAST:event_onBaseLengthChange

    private void onOutputFileChanged(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_onOutputFileChanged
        File oldValue = getOutputFile();
        File newValue = new File(outputFileField.getText());
        if (oldValue == null || newValue == null || 
                oldValue.getAbsoluteFile().equals(newValue.getAbsoluteFile()) == false) {
            setOutputFile(newValue);
        }
    }//GEN-LAST:event_onOutputFileChanged

    private void onRecursionDepthChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_onRecursionDepthChanged
        int oldValue = getRecursionDepth();
        int newValue = (Integer) recursionDepthField.getModel().getValue();
        if (oldValue != newValue) {
            setRecursionDepth(newValue);
        }
    }//GEN-LAST:event_onRecursionDepthChanged

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable()     {

            public void run() {
                new MainFrame().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JFormattedTextField baseLengthField;
    private javax.swing.JButton cancelButton;
    private javax.swing.JButton generateButton;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JTextField outputFileField;
    private javax.swing.JSpinner recursionDepthField;
    private javax.swing.JButton resetButton;
    private javax.swing.JButton setButton;
    // End of variables declaration//GEN-END:variables
}
