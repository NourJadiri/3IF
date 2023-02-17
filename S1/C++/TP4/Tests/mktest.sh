echo "Test ID;Return code validation;Out result;StdErr result;File creation result;Global result" >results.csv
nOk=0
nKo=0
nTotal=0
nMis=0

for i in Test*
do
  # gestion des cas particuliers (commande -g)

  # il faut notamment retrouver les anciens contenus des fichiers qui doivent servir pour tester
  # lorsqu'un fichier non vide est donné sur la ligne de commande
  # (et donc verifier si on ecrase bien le contenu ou pas)

  # par precaution, si jamais l'utilisateur execute a la main les tests qui produisent un fichier dot
  # et qu'il ne les efface pas apres les avoir crees, nous avons decide a la fois de mettre
  # une commande dans ce script shell qui permet d'effacer ces fichiers, et nous le remettons egalement
  # dans les fichiers run des tests en question pour eviter un bug du test s'il est execute seul.
  # sinon, il y aura une attente d'entree de l'application pour savoir s'il faut ecraser le contenu
  # du fichier ou choisir un autre fichier

  # nous n'avons pas mis les lignes de commandes pour la copie dans les fichier run car certes cela
  # peut poser probleme pour le resultat du test, mais cela n'empechera pas le deroulement total des tests

  # nous supposons donc que l'utilisateur sait faire bon usage d'un framework de tests, et qu'il
  # ne les testeras pas un par un a la main sans prendre de precautions au prealable, mais qu'il
  # utilisera ce script shell pour les executer correctement.

  test_num=${i#Test} # pour caster le numero du test en int

  if [ $test_num -eq 8 ] || [ $test_num -eq 9 ] || [ $test_num -eq 18 ] || [ $test_num -eq 25 ] || [ $test_num -eq 27 ]
  then
    rm -f $i/shortTest.dot
  elif [ $test_num -eq 11 ] || [ $test_num -eq 12 ] || [ $test_num -eq 14 ] || [ $test_num -eq 32 ]
  then
    cp $i/shortTest_Old.dot $i/shortTest.dot
  elif [ $test_num -eq 13 ]
  then
    cp $i/dontTouchTest_old.dot $i/dontTouchTest.dot
    rm -f $i/touchTest_old.dot
  fi

  # fin de la gestion des cas particuliers lies a la commande -g

  ./test.sh $i results.csv

  result=$?
  if [ $result -eq 0 ]
  then
    let "nKo=$nKo+1"
  elif [ $result -eq 1 ]
  then
    let "nOk=$nOk+1"
  else
    let "nMis=$nMis+1"
  fi
  let "nTotal=$nTotal+1"
done

echo "Passed tests     : $nOk"
echo "Failed tests     : $nKo"
echo "Misformed tests  : $nMis"
echo "-----------------------"
echo "Total            : $nTotal"
