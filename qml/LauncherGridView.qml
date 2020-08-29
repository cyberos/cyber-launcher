import QtQuick 2.0
import org.cyber.launcher 1.0

PagedGrid {
    id: gridView

    property alias query: appsProxyModel.filterPattern
    property int cellSize: 130
    property int sideMargins: root.width * 0.1
    property int itemSize: root.height * 0.15

    rows: 4
    columns: 6

    width: columns * itemSize
    height: rows * itemSize

//    anchors.leftMargin: sideMargins
//    anchors.rightMargin: sideMargins

    model: SortFilterProxyModel {
        id: appsProxyModel
        sourceModel: applicationManager
        filterRoleName: "filterInfo"
        filterCaseSensitivity: Qt.CaseInsensitive
        isSortLocaleAware: true
        sortCaseSensitivity: Qt.CaseSensitive
        sortOrder: Qt.AscendingOrder
        sortRoleName: "name"
    }

    delegate: Item {
        width: gridView.itemSize
        height: width

        LauncherGridDelegate {
            id: delegate

            anchors {
                fill: parent
                margins: 10
            }
        }
    }
}
