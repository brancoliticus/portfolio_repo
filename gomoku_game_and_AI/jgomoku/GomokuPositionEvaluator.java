 /*
  *Copyright 2008 Cristian Achim
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing,
  * software distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  */

package jgomoku;

import java.util.*;
import jgomoku.GomokuMoveProposer.*;

public class GomokuPositionEvaluator {

    private List<Move> blackFoursUncapped;
    private List<Move> whiteFoursUncapped;
    private List<Move> blackFoursCapped;
    private List<Move> whiteFoursCapped;

    private List<DirectionMove> lineEnders;

    private static int size=15;
    private int row , column;
    private int length , aux , i;

    private int blackStones;
    private int whiteStones;

    private Move[] moveHistory;

    private char[][] gomokuPosition;
    private boolean blackToMove;

    private char currentDirection;

    private BoardLocationComparator boardLocationComparator=
            new BoardLocationComparator();

    private ValueMoveComparator valueMoveComparator=
            new ValueMoveComparator();

    private boolean uncapped;

    public GomokuPositionEvaluator(){
        int index;

        lineEnders=new ArrayList<DirectionMove>();

        blackFoursUncapped=new ArrayList<Move>();
        whiteFoursUncapped=new ArrayList<Move>();
        blackFoursCapped=new ArrayList<Move>();
        whiteFoursCapped=new ArrayList<Move>();

        moveHistory=new Move[20];
        for(index=0;index<20;index++){
            moveHistory[index]=new Move();
        }
    }

    private void cleanUpLists(){
        lineEnders=new ArrayList<DirectionMove>();

        blackFoursUncapped=new ArrayList<Move>();
        whiteFoursUncapped=new ArrayList<Move>();
        blackFoursCapped=new ArrayList<Move>();
        whiteFoursCapped=new ArrayList<Move>();

        finalMoveList=new ArrayList<ValueMove>();
    }

    private void addBlackUncapped(int index){
        switch(blackStones){
            case 1:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        true ,currentDirection ,
                        1 , false));
                break;
            case 2:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        true , currentDirection ,
                        2 , false));
                break;
            case 3:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        true , currentDirection ,
                        3 , false));
                break;
            case 4:
                blackFoursUncapped.add(
                        new Move(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column));
                break;
        }
    }

    private void addWhiteUncapped(int index){
        switch(whiteStones){
            case 1:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        false , currentDirection ,
                        1 , false));
                break;
            case 2:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        false , currentDirection ,
                        2 , false));
                break;
            case 3:
                lineEnders.add(
                       new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        false , currentDirection ,
                        3 , false));
                break;
            case 4:
                whiteFoursUncapped.add(
                        new Move(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column));
                break;
        }
    }

    private void addBlackCapped(int index){
        switch(blackStones){
            case 1:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        true , currentDirection ,
                        1 , true));
                break;
            case 2:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        true , currentDirection ,
                        2 , true));
                break;
            case 3:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        true , currentDirection ,
                        3 , true));
                break;
            case 4:
                blackFoursCapped.add(
                        new Move(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column));
                break;
        }
    }

    private void addWhiteCapped(int index){
        switch(whiteStones){
            case 1:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        false , currentDirection ,
                        1 , true));
                break;
            case 2:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        false , currentDirection ,
                        2 , true));
                break;
            case 3:
                lineEnders.add(
                        new DirectionMove(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column ,
                        false , currentDirection ,
                        3 , true));
                break;
            case 4:
                whiteFoursCapped.add(
                        new Move(
                        moveHistory[length-index].row ,
                        moveHistory[length-index].column));
                break;
        }
    }

    private void inLineStuff(boolean outOfLine){// outOfLine=true
                        // treat the case of stone lines that end
                        // at the board edge

        if(outOfLine == true){
            if(blackStones != 0){
                try{
                    if(gomokuPosition[moveHistory[length-(blackStones+2)].row]
                        [moveHistory[length-(blackStones+2)].column] == 'o'){

                        addBlackCapped(blackStones+2); // go back in line
                                        // with black stones + 1
                    }
                }
                catch(IndexOutOfBoundsException e){
                }
            }

            if(whiteStones != 0){
                try{
                    if(gomokuPosition[moveHistory[length-(whiteStones+2)].row]
                        [moveHistory[length-(whiteStones+2)].column] == 'o'){

                        addWhiteCapped(whiteStones+2);
                    }
                }
                catch(IndexOutOfBoundsException e){
                }
            }

            return;
        }



        moveHistory[length].row=row;
        moveHistory[length].column=column;

        length++;

        switch(gomokuPosition[row][column]){
            case 'o':
                if(blackStones != 0){
                    uncapped=false;
                    try{
                        if(gomokuPosition[moveHistory[length-(blackStones+2)].row]
                                [moveHistory[length-(blackStones+2)].column] == 'o'){

                            addBlackUncapped(blackStones+2);
                            addBlackUncapped(1);
                            uncapped=true;
                        }
                    }
                    catch(IndexOutOfBoundsException e){
                    }
                    finally{
                        if(!uncapped){
                            addBlackCapped(1);
                        }
                    }

                    blackStones=0;
                }
                if(whiteStones != 0){
                    uncapped=false;
                    try{
                        if(gomokuPosition[moveHistory[length-(whiteStones+2)].row]
                                [moveHistory[length-(whiteStones+2)].column] == 'o'){

                            addWhiteUncapped(whiteStones+2);
                            addWhiteUncapped(1);
                            uncapped=true;
                        }
                    }
                    catch(IndexOutOfBoundsException e){
                    }
                    finally{
                        if(!uncapped){
                            addWhiteCapped(1);
                        }
                    }

                    whiteStones=0;
                }
                break;
            case 'b':
                blackStones++;
                if(whiteStones != 0){
                    try{
                        if(gomokuPosition[moveHistory[length-(whiteStones+2)].row]
                                [moveHistory[length-(whiteStones+2)].column] == 'o'){

                            addWhiteCapped(whiteStones+2);
                        }
                    }
                    catch(IndexOutOfBoundsException e){
                    }

                    whiteStones=0;
                }
                break;
            case 'w':
                whiteStones++;
                if(blackStones != 0){
                    try{
                        if(gomokuPosition[moveHistory[length-(whiteStones+2)].row]
                                [moveHistory[length-(whiteStones+2)].column] == 'o'){

                            addBlackCapped(blackStones+2);
                        }
                    }
                    catch(IndexOutOfBoundsException e){
                    }

                    blackStones=0;
                }
                break;
        }


    }

    private DirectionMove currentMove , previousMove=null;
    private int currentMoveValue;
    private List<ValueMove> finalMoveList;

    private void inLocationStuff() {
        if (previousMove == null) {
            currentMoveValue+=currentMove.cappedLine ?
                currentMove.stoneCount*9 : currentMove.stoneCount*3;
            return;
        }
        if (currentMove.row == previousMove.row &&
                currentMove.column == previousMove.column) {
            if (currentMove.direction == previousMove.direction &&
                    currentMove.isBlackMove == previousMove.isBlackMove) {
                if (currentMove.stoneCount + previousMove.stoneCount > 4) {
                    if (currentMove.isBlackMove) {
                        blackFoursUncapped.add(currentMove);
                    }
                    else {
                        whiteFoursUncapped.add(currentMove);
                    }
                }
            }

            currentMoveValue +=currentMove.cappedLine ?
                currentMove.stoneCount * 9 : currentMove.stoneCount * 3;

        }
        else {
            finalMoveList.add(new ValueMove(previousMove.row ,
                    previousMove.column , currentMoveValue));
            currentMoveValue=currentMove.cappedLine ?
                currentMove.stoneCount*9 : currentMove.stoneCount*3;
        }
    }

    public int getPositionValue(char[][] gomokuPosition ,
            boolean blackToMove){

        this.gomokuPosition=gomokuPosition;
        this.blackToMove=blackToMove;

        cleanUpLists();

        //all lines
        this.currentDirection=DirectionMove.HORIZONTAL;
        for(row=0 ; row<size ; row++){
            length=0;
            blackStones=0;
            whiteStones=0;
            for(column=0 ; column<size ; column++){
                inLineStuff(false);
            }
            inLineStuff(true);
        }

        //all columns
        this.currentDirection=DirectionMove.VERTICAL;
        for(column=0 ; column<size ; column++){
            length=0;
            blackStones=0;
            whiteStones=0;
            for(row=0 ; row<size ; row++){
                inLineStuff(false);
            }
            inLineStuff(true);
        }

        //diagonals above , parallel to and including the main board matrice diagonal
        this.currentDirection=DirectionMove.FIRSTDIAGONAL;
        for(aux=0 ; aux<size ; aux++){
            length=0;
            blackStones=0;
            whiteStones=0;
            for(column=size-1-aux , row=0 ; column<size ; column++ , row++){
                inLineStuff(false);
            }
            inLineStuff(true);
        }

        //diagonals below and parallel to the main board matrice diagonal
        for(aux=0 ; aux<size-1 ; aux++){
            length=0;
            blackStones=0;
            whiteStones=0;
            for(row=size-1-aux , column=0 ; row<=size-1 ; row++ , column++){
                inLineStuff(false);
            }
            inLineStuff(true);
        }

        //diagonals above , parallel to and including the secondary board matrice diagonal
        this.currentDirection=DirectionMove.SECONDDIAGONAL;
        for(aux=0 ; aux<size ; aux++){
            length=0;
            blackStones=0;
            whiteStones=0;
            for(row=aux , column=0 ; row>=0 ; row-- , column++){
                inLineStuff(false);
            }
            inLineStuff(true);
        }

        //diagonals below and parallel to the secondary board matrice diagonal
        for(aux=0 ; aux<size-1 ; aux++){
            length=0;
            blackStones=0;
            whiteStones=0;
            for(column=size-1-aux , row=size-1 ; column<=size-1 ; column++ , row--){
                inLineStuff(false);
            }
            inLineStuff(true);
        }

        if(blackToMove){
            //winning moves black
            if(! blackFoursUncapped.isEmpty()){
                return blackToMove ? 1000000 : -1000000;
            }
            if(! blackFoursCapped.isEmpty()){
                return blackToMove ? 1000000 : -1000000;
            }
            // obligatory moves black
            if(! whiteFoursUncapped.isEmpty()){
                return blackToMove ? -100000 : 1000000;
            }
            if(! whiteFoursCapped.isEmpty()){
                return blackToMove ? -100000 : 1000000;
            }
        }
        else{
            // winning moves white
            if(! whiteFoursUncapped.isEmpty()){
                return blackToMove ? -100000 : 1000000;
            }
            if(! whiteFoursCapped.isEmpty()){
                return blackToMove ? -100000 : 1000000;
            }
            // obligatiry moves white
            if(! blackFoursUncapped.isEmpty()){
                return blackToMove ? 1000000 : -1000000;
            }
            if(! blackFoursCapped.isEmpty()){
                return blackToMove ? 1000000 : -1000000;
            }
        }

        Collections.sort(lineEnders , boardLocationComparator);

        Iterator<DirectionMove> it=lineEnders.iterator();
        while(it.hasNext()){
            currentMove=it.next();
            inLocationStuff();
            previousMove=currentMove;
        }
        finalMoveList.add(new ValueMove(currentMove.row ,
                currentMove.column , currentMoveValue));

        if(blackToMove){
            //winning moves black
            if(! blackFoursUncapped.isEmpty()){
                return blackToMove ? 1000000 : -1000000;
            }
            // obligatory moves black
            if(! whiteFoursUncapped.isEmpty()){
                return blackToMove ? -1000000 : 1000000;
            }
        }
        else{
            // winning moves white
            if(! whiteFoursUncapped.isEmpty()){
                return blackToMove ? -1000000 : 1000000;
            }
            // obligatiry moves white
            if(! blackFoursUncapped.isEmpty()){
                return blackToMove ? 1000000 : -1000000;
            }
        }

        int returnValue=0;
        int aux;
        Iterator<ValueMove> it1=finalMoveList.iterator();
        while(it1.hasNext()){
            aux=it1.next().moveValue;
            if(Math.abs(aux) > Math.abs(returnValue)){
                returnValue=aux;
            }
        }

        return blackToMove ? returnValue : -returnValue;
    }
}