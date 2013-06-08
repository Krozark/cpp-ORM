-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Client: localhost
-- Généré le : Ven 07 Juin 2013 à 11:59
-- Version du serveur: 5.5.31
-- Version de PHP: 5.3.10-1ubuntu3.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `test`
--

-- --------------------------------------------------------

--
-- Structure de la table `perso`
--

CREATE TABLE IF NOT EXISTS `perso` (
  `name` varchar(255) NOT NULL,
  `stats` int(11) NOT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `lvl` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `stats` (`stats`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Contenu de la table `perso`
--

INSERT INTO `perso` (`name`, `stats`, `id`, `lvl`) VALUES
('test1', 1, 1, 17);

-- --------------------------------------------------------

--
-- Structure de la table `stats`
--

CREATE TABLE IF NOT EXISTS `stats` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pv` int(11) NOT NULL DEFAULT '0',
  `pi` int(11) NOT NULL DEFAULT '0',
  `int` int(11) NOT NULL DEFAULT '0',
  `force` int(11) NOT NULL DEFAULT '0',
  `def` int(11) NOT NULL DEFAULT '0',
  `vatq` int(11) NOT NULL DEFAULT '0',
  `esq` int(11) NOT NULL DEFAULT '0',
  `chance` int(11) NOT NULL DEFAULT '0',
  `charme` int(11) NOT NULL DEFAULT '0',
  `mouvement` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Contenu de la table `stats`
--

INSERT INTO `stats` (`id`, `pv`, `pi`, `int`, `force`, `def`, `vatq`, `esq`, `chance`, `charme`, `mouvement`) VALUES
(1, 42, 12, 4, 5, 2, 8, 0, 1, 1, 3);

--
-- Contraintes pour les tables exportées
--

--
-- Contraintes pour la table `perso`
--
ALTER TABLE `perso`
  ADD CONSTRAINT `perso_ibfk_1` FOREIGN KEY (`stats`) REFERENCES `stats` (`id`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
