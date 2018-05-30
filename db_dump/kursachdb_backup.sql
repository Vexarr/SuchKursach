-- MySQL dump 10.13  Distrib 5.7.22, for Linux (x86_64)
--
-- Host: localhost    Database: mydb
-- ------------------------------------------------------
-- Server version	5.7.22-0ubuntu0.16.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Должности`
--

DROP TABLE IF EXISTS `Должности`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Должности` (
  `idДолжности` int(11) NOT NULL AUTO_INCREMENT,
  `Должность` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`idДолжности`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Должности`
--

LOCK TABLES `Должности` WRITE;
/*!40000 ALTER TABLE `Должности` DISABLE KEYS */;
INSERT INTO `Должности` VALUES (1,'Продавец'),(2,'Менеджер'),(3,'Консультант');
/*!40000 ALTER TABLE `Должности` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Магазин`
--

DROP TABLE IF EXISTS `Магазин`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Магазин` (
  `idМагазина` int(11) NOT NULL AUTO_INCREMENT,
  `Название` varchar(20) NOT NULL,
  `Адрес` varchar(45) DEFAULT NULL,
  `Телефон` varchar(20) NOT NULL,
  PRIMARY KEY (`idМагазина`),
  UNIQUE KEY `idМагазина_UNIQUE` (`idМагазина`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Магазин`
--

LOCK TABLES `Магазин` WRITE;
/*!40000 ALTER TABLE `Магазин` DISABLE KEYS */;
INSERT INTO `Магазин` VALUES (1,'Пятый калибр','г. Томск, пр. Ленина, 66','8-800-555-35-35'),(2,'Пятый калибр','г. Томск, ул. Красноармейская, 25','8-800-555-35-35'),(3,'Пятый калибр','г. Томск, ул. Киевская, 82','8-800-555-35-35');
/*!40000 ALTER TABLE `Магазин` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Персонал`
--

DROP TABLE IF EXISTS `Персонал`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Персонал` (
  `idПерсонала` int(11) NOT NULL AUTO_INCREMENT,
  `ФИО` varchar(60) DEFAULT NULL,
  `idПол` int(11) DEFAULT NULL,
  `idДолжности` int(11) DEFAULT NULL,
  PRIMARY KEY (`idПерсонала`),
  KEY `idПол` (`idПол`),
  KEY `idДолжности` (`idДолжности`),
  CONSTRAINT `Персонал_ibfk_1` FOREIGN KEY (`idПол`) REFERENCES `Пол` (`idПола`) ON DELETE SET NULL,
  CONSTRAINT `Персонал_ibfk_2` FOREIGN KEY (`idДолжности`) REFERENCES `Должности` (`idДолжности`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=37 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Персонал`
--

LOCK TABLES `Персонал` WRITE;
/*!40000 ALTER TABLE `Персонал` DISABLE KEYS */;
INSERT INTO `Персонал` VALUES (33,'Константин Сергеевич Штольц',2,3),(34,'Сергей Михайлович Соколов',2,1),(35,'Марина Андреевна Баркович',1,2),(36,'Дмитрий Борисович Шмель',2,1);
/*!40000 ALTER TABLE `Персонал` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Покупки`
--

DROP TABLE IF EXISTS `Покупки`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Покупки` (
  `idПокупки` int(11) NOT NULL AUTO_INCREMENT,
  `Количество` int(11) NOT NULL,
  `idМагазина` int(11) NOT NULL,
  `idПерсонала` int(11) NOT NULL,
  `Дата_продажи` varchar(15) NOT NULL,
  PRIMARY KEY (`idПокупки`),
  UNIQUE KEY `idПокупки_UNIQUE` (`idПокупки`),
  KEY `fk_Покупки_1_idx` (`idМагазина`),
  KEY `fk_Покупки_2_idx` (`idПерсонала`),
  CONSTRAINT `fk_Покупки_1` FOREIGN KEY (`idМагазина`) REFERENCES `Магазин` (`idМагазина`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_Покупки_2` FOREIGN KEY (`idПерсонала`) REFERENCES `Персонал` (`idПерсонала`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Покупки`
--

LOCK TABLES `Покупки` WRITE;
/*!40000 ALTER TABLE `Покупки` DISABLE KEYS */;
INSERT INTO `Покупки` VALUES (15,2,1,34,'18.04.2018'),(16,1,1,34,'02.05.2018'),(17,2,2,36,'21.05.2018');
/*!40000 ALTER TABLE `Покупки` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Пол`
--

DROP TABLE IF EXISTS `Пол`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Пол` (
  `idПола` int(11) NOT NULL AUTO_INCREMENT,
  `Пол` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`idПола`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Пол`
--

LOCK TABLES `Пол` WRITE;
/*!40000 ALTER TABLE `Пол` DISABLE KEYS */;
INSERT INTO `Пол` VALUES (1,'Женский'),(2,'Мужской');
/*!40000 ALTER TABLE `Пол` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Структура_покупки`
--

DROP TABLE IF EXISTS `Структура_покупки`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Структура_покупки` (
  `idСтруктура_покупки` int(11) NOT NULL AUTO_INCREMENT,
  `idПокупки` int(11) NOT NULL,
  `idТовара` int(11) NOT NULL,
  `Количество_товара` int(11) DEFAULT NULL,
  PRIMARY KEY (`idСтруктура_покупки`),
  UNIQUE KEY `idСтруктура_покупки_UNIQUE` (`idСтруктура_покупки`),
  KEY `fk_Структура_покупки_1_idx` (`idПокупки`),
  KEY `fk_Структура_покупки_2_idx` (`idТовара`),
  CONSTRAINT `fk_Структура_покупки_1` FOREIGN KEY (`idПокупки`) REFERENCES `Покупки` (`idПокупки`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_Структура_покупки_2` FOREIGN KEY (`idТовара`) REFERENCES `Товары` (`idТовара`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Структура_покупки`
--

LOCK TABLES `Структура_покупки` WRITE;
/*!40000 ALTER TABLE `Структура_покупки` DISABLE KEYS */;
INSERT INTO `Структура_покупки` VALUES (6,15,1,1),(8,16,5,3),(9,17,5,2),(10,17,6,1);
/*!40000 ALTER TABLE `Структура_покупки` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Товары`
--

DROP TABLE IF EXISTS `Товары`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Товары` (
  `idТовара` int(11) NOT NULL AUTO_INCREMENT,
  `Наименование` varchar(100) NOT NULL,
  `Артикул` varchar(15) NOT NULL,
  `Цена` double NOT NULL,
  `Описание` varchar(500) DEFAULT NULL,
  `Наличие_на_складе` int(11) NOT NULL,
  `Фото` binary(1) DEFAULT NULL,
  PRIMARY KEY (`idТовара`),
  UNIQUE KEY `idТовара_UNIQUE` (`idТовара`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Товары`
--

LOCK TABLES `Товары` WRITE;
/*!40000 ALTER TABLE `Товары` DISABLE KEYS */;
INSERT INTO `Товары` VALUES (1,'Рекурсивный арбалет FOX (Фокс)','1864b2',9700,'Легкий, простой в техническом оснащении и эксплуатации арбалет, идеален как для начинающих арбалетчиков, так и опытных стрелков',9,NULL),(2,'Стрела карбоновая 20 Crossbolt','4315g6',450,'Стрела большой длины 20 дюймов, изготовленная из сверхпрочного карбона (углепластика). Обладает улучшенными баллистическими свойствами и практически идеальным балансом. Это позволяет использовать ее для развлекательной стрельбы, в спортивных состязаниях и даже на охоте. Стрела карбоновая \"20 Crossbolt\" применяется совместно с арбалетами всех распространенных видов, рассчитанных на типоразмер 20\"',150,NULL),(3,'Ружье Breda Echo Grey к.12/76/760','8452f1',120000,'Breda Echo - это традиционное охотничье полуавтоматическое ружьё калибра 12х76 великолепного качества изготовления. Ствольная коробка выполнена из алюминиевого сплава, магазин ружья вмещает 3 патрона с длиной гильзы 76 мм и 4 с 70-мм гильзой, затвор поворотный, возвратная пружина размещена в прикладе. Схема работы автоматики - инерционная, так полюбившаяся в ружьях Benelli, без отвода газов из канала ствола',5,NULL),(4,'Патрон S&B .22 WMR 2,6 г FMJ 50 шт.','217k65',1700,'Патроны к оружию с нарезным стволом',300,NULL),(5,'Винтовка пневматическая EVANIX AVALANCHE (SHB,Black) к.4,5 ','78452j',120000,'Инновационный карабин РСР с резервуаром объема 260 см3, установленным спереди, и композитным баллоном объема 460 см3, установленным сзади. Это позволяет сделать до 90 выстрелов с превосходной точностью и мощностью. Брутальный и лаконичный дизайн винтовки понравится людям, серьезно увлекающимся охотой и стрельбой по мишеням. Для установки оптики имеется \"ласточкин хвост\" (11 мм), магазин изготовлен из алюминия',10,NULL),(6,'Карабин Blaser R93 LRS-2 .300 WinMag 627mm ','68213j',660000,'Снайперская винтовка Blaser R93 LRS-2 является закономерным результатом развития популярного охотничего карабина R93',6,NULL);
/*!40000 ALTER TABLE `Товары` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-05-30 15:12:40
