import { ImageType } from "@/image";
import { getImageData } from '@/http-api';

export class ImageDisplay {
    _info: ImageType;
    _element: HTMLImageElement;

    constructor(element:HTMLImageElement, info:ImageType){
        this._info = info;
        this._element = element;
        this.updateUpstream();
    }

    getId(){ return this._info.id; }
    getName(){ return this._info.name; }
    getType(){ return this._info.type; }
    getSize(){ return this._info.size; }
    getElement(){ return this._element; }

    setInfo(newInfo: ImageType) {
        this._info = newInfo;
        this.updateUpstream();
    }
    
    setElementSrc(src: string){
        if(src) this._element?.setAttribute("src",src);
    }

    updateUpstream(){
        getImageData(this.getId())
        .then((result) => this.setElementSrc(result))
        .catch( (e) => console.log(e))
    }
}
