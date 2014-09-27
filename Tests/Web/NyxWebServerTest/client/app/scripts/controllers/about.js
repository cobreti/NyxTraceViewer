'use strict';

/**
 * @ngdoc function
 * @name nyxClientWebTestApp.controller:AboutCtrl
 * @description
 * # AboutCtrl
 * Controller of the nyxClientWebTestApp
 */
angular.module('nyxClientWebTestApp')
  .controller('AboutCtrl', function ($scope) {
    $scope.awesomeThings = [
      'HTML5 Boilerplate',
      'AngularJS',
      'Karma'
    ];
  });
